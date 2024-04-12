%{
    #include <stdio.h>
    #define YYDEBUG 1
    //#include "symtablehash.h"
    #include "SymTable.h"
    //#define YYLEX alpha_yylex
    extern int yydebug;
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);
    SymbolTableEntry *entry;
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T symTable = NULL;
    int anonymousCounter = 0;
    int scope = 0;
%}

%union{
    int intv;
    char* stringv;
    char charv;
    float floatv;
}

%define parse.error verbose
%start program

%token <intv> INTEGER "integer constant"
%token <floatv> REAL "real contstant"


%token <stringv> KEYWORD_IF KEYWORD_THEN KEYWORD_ELSE KEYWORD_WHILE 
%token <stringv> KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_RETURN KEYWORD_BREAK KEYWORD_CONTINUE
%token <stringv> KEYWORD_AND KEYWORD_NOT KEYWORD_OR KEYWORD_LOCAL KEYWORD_TRUE
%token <stringv> KEYWORD_FALSE KEYWORD_NIL GREATER LESS EQUALS
%token <stringv> GREATER_EQUAL LESS_EQUAL NOT_EQUAL INCREMENT DECREMENT 
%token <stringv> STRING
%token <stringv> IDENTIFIER LEFTBRACE RIGHTBRACE LEFTBRACKET RIGHTBRACKET 
%token <stringv> LEFTPARENTHESIS RIGHTPARENTHESIS COMMA SEMICOLON COLON 
%token <stringv> DOT DOUBLEDOT DOUBLECOLON 

/*
%type <stringv> program parsing stmt expr term assignexpr primary lvalue member call callsuffix normcall methodcall elist exprlist objectdef obj indexed indexedelem block blockk funcdef const number idlist ifstmt whilestmt forstmt returnstmt
*/

%right '='
%left KEYWORD_OR
%left KEYWORD_AND
%left '+' '-'
%left '*' '/' '%'
%right KEYWORD_NOT INCREMENT DECREMENT 
%left DOT DOUBLEDOT
%left LEFTBRACKET RIGHTBRACKET
%left LEFTPARENTHESIS RIGHTPARENTHESIS 

%nonassoc EQUALS NOT_EQUAL
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL 
%nonassoc UMINUS

%%

program:            parsing {printf("program -> parsing");}            
                    ;
parsing:            stmt parsing {printf("parsing -> stmt parsing");}       
                    | stmt {printf("parsing -> stmt");}
                    ;

stmt:               expr SEMICOLON {printf("stmt -> expr;");}
                    | ifstmt {printf("stmt -> ifstmt");}
                    | whilestmt {printf("stmt -> whilestmt");}
                    | forstmt {printf("stmt -> forstmt");}
                    | returnstmt {printf("stmt -? returnstmt");}
                    | KEYWORD_BREAK SEMICOLON {printf("stmt -> break;");}
                    | KEYWORD_CONTINUE SEMICOLON {printf("stmt -> coninue;");}
                    | block {printf("stmt -> block");}
                    | funcdef {printf("stmt -> funcdef");}
                    | SEMICOLON {printf("stmt -> ;");}
                    | error SEMICOLON   { yyerrok; }
                    ;

expr:                 expr '+' expr {printf("expr -> expr + expr");}        
                    | expr '-' expr {printf("expr -> expr - expr");}        
                    | expr '*' expr {printf("expr -> expr * expr");}        
                    | expr '/' expr {printf("expr -> expr / expr");}        
                    | expr '%' expr {printf("expr -> expr % expr");}        
                    | expr GREATER expr {printf("expr -> expr > expr");}     
                    | expr GREATER_EQUAL expr {printf("expr -> expr >= expr");}
                    | expr LESS expr {printf("expr -> expr < expr");}         
                    | expr LESS_EQUAL expr {printf("expr -> expr <= expr");}    
                    | expr EQUALS expr {printf("expr -> expr == expr");}       
                    | expr NOT_EQUAL expr {printf("expr -> expr != expr");}    
                    | expr KEYWORD_AND expr {printf("expr -> expr && expr");}    
                    | expr KEYWORD_OR expr {printf("expr -> expr || expr");}   
                    | assignexpr {printf("expr -> assignexpr");}             
                    | term {printf("expr -> term");}
                    ;


term:               LEFTPARENTHESIS expr RIGHTPARENTHESIS {printf("term -> (expr)");}
                    | '-' expr %prec UMINUS {printf("term -> -expr");}
                    | KEYWORD_NOT expr {printf("term -> !expr");}
                    | INCREMENT lvalue {printf("term -> ++lvalue");}
                    | lvalue INCREMENT {printf("term -> lvalue++");}
                    | DECREMENT lvalue {printf("term -> --lvalue");}
                    | lvalue DECREMENT {printf("term -> lvalue--");}
                    | primary {printf("term -> primary");}

assignexpr:         lvalue '=' expr { 
                                        if(entry == NULL){
                                            yyerror("Error: Invalid assignment");         
                                        }
                                        if(entry->type == USERFUNC || entry->type == LIBFUNC){
                                            yyerror("Error: function assignment");
                                        }
                                        printf("assignexpr -> lvalue = expr");
                                    }

primary:            lvalue {printf("primary -> lvalue");}
                    | call {printf("primary -> call");}
                    | objectdef {printf("primary -> objectdef");}
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  {printf("primary -> (funcdef)");}
                    | const {printf("primary -> const");}

lvalue:             IDENTIFIER {    
                                    /*check every scope "inside out"
                                    int flag = 0;
                                    int tmp = scope;
                                    while(tmp >= 0 && flag == 0){
                                        entry = lookup($1, tmp);
                                        if(entry != NULL) flag = 1;
                                        tmp--;
                                    } not needed cause i changed the lookup*/
                                     entry = lookup($1, scope);
                                    //if we dont find the identifier in any scope we add it to the st
                                    if(flag == 0){
                                        if (scope == 0) {
                                            entry = insert($1, GLOBAL, 0, yylineno);
                                        } else {
                                            entry = insert($1, LOCAL, scope, yylineno);
                                        }
                                    }
                                    //access rules
                                    else{
                                        if (!entry->isActive) yyerror("identifier error"); //if hidden, error
                                        else{
                                            //need to implement access rules
                                        }                                                  
                                    }
                                }

                    | KEYWORD_LOCAL IDENTIFIER {  
                                                entry = lookup_in_scope($2, scope); 
                                                if (entry == NULL) {
                                                    entry = lookup($2, scope);
                                                    if (entry != NULL && entry->type == LIBFUNC && scope != 0) {
                                                        yyerror("Cannot shadow a library function");
                                                    } else {
                                                        if (scope == 0) {
                                                            entry = insert($2, GLOBAL, scope, yylineno);
                                                        } else {
                                                            entry = insert($2, LOCAL, scope, yylineno);
                                                        }
                                                    }
                                                }
                                            }

                    | DOUBLECOLON IDENTIFIER   {
                                                    entry = lookup($2, 0); 
                                                    if (entry == NULL || !entry->isActive) printf("global identifier not found");
                                                    //not inserting is st when ::
                                                    //need to implement 
                                                }
                    | member

member:             lvalue DOT IDENTIFIER   { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue.id");

                                            }            
                    | lvalue LEFTBRACKET expr RIGHTBRACKET { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue[expr]");
                                            }
                    | call DOT IDENTIFIER               
                    | call LEFTBRACKET expr RIGHTBRACKET

call:               call LEFTPARENTHESIS elist RIGHTPARENTHESIS
                    | lvalue callsuffix
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS

callsuffix:         normcall
                    | methodcall

normcall:           LEFTPARENTHESIS elist RIGHTPARENTHESIS

methodcall:         DOUBLEDOT IDENTIFIER LEFTPARENTHESIS elist RIGHTPARENTHESIS 

elist:              exprlist
                    | %empty            {}
                    ;

exprlist:           exprlist  COMMA expr
                    | expr
                    ;
             

objectdef:          LEFTBRACKET  obj RIGHTBRACKET 
                    | LEFTBRACKET RIGHTBRACKET
                    ;

obj:                elist
                    | indexed
                    ;
                    
indexed:            indexedelem  COMMA indexed  
                    | indexedelem
                    ;

indexedelem:        LEFTBRACE expr COLON expr RIGHTBRACE

block:              LEFTBRACE  { scope++; } blockk  RIGHTBRACE { scope--; }
                    ;

blockk:              stmt blockk
                    | %empty            {}
                    ;

funcdef:            KEYWORD_FUNCTION  IDENTIFIER LEFTPARENTHESIS idlist RIGHTPARENTHESIS block {
    
                        entry = lookup($2, scope); 
                        if (entry != NULL){
                            //check collision with library/user functions or variables
                            if (entry->type == LIBFUNC) yyerror("library function collision");
                            else if (entry->type == USERFUNC) yyerror("user function collision");
                            else yyerror("variable collision");
                        } 
                        else {
                            entry = insert($2, USERFUNC, scope, yylineno);
                            //only increment scope if function is valid
                            scope++;
                        }
    }     
                    | KEYWORD_FUNCTION  { 
                        char str[20]; 
                        fprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, 0, yylineno); 
                        scope++;
                        } 
                        LEFTPARENTHESIS idlist RIGHTPARENTHESIS block          
                    ;
const:              number | STRING | KEYWORD_NIL | KEYWORD_TRUE | KEYWORD_FALSE

number:             INTEGER 
                    | REAL
                    ;
idlist:             IDENTIFIER COMMA idlist  {  
                                                entry = lookup($1, ++scope);//lookup in function scope
                                                if(entry != NULL) yyerror("identifier error");
                                                else if (entry->type == LIBFUNC) yyerror("library function collision");
                                                else entry = insert($1,FORMAL,0,yylineno);   
                                            }
                    | IDENTIFIER             {  entry = lookup($1, ++scope);//lookup in function scope
                                                if(entry != NULL) yyerror("identifier error");
                                                else if (entry->type == LIBFUNC) yyerror("library function collision");
                                                else entry = insert($1,FORMAL,0,yylineno);     }
                    | %empty                 {}
                    ;

ifstmt:             KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt  KEYWORD_ELSE stmt 
                    | KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt

whilestmt:          KEYWORD_WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt

forstmt:            KEYWORD_FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS stmt

returnstmt:         KEYWORD_RETURN  expr  SEMICOLON
                    | KEYWORD_RETURN SEMICOLON

%%
int yyerror (char* yaccProvidedMessage) {
    fprintf(stderr, "%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr,"INPUT NOT VALID\n");
    return 1;
}

//**************************************************************

int main(int argc,char **argv){
    //yydebug = 1;
    symTable = SymTable_new();
    initialize_scope_links();
    insert_libfuncs();
    char *libfuncs[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin"};
    
    if(argc > 1){
        if(!(yyin = fopen(argv[1],"r"))){
            fprintf(stderr,"Cannot open file\n");
            return 1;
        }
    }else{
        yyin = stdin;
    }
    yyparse();

    printf("PRINTING SYMBOL TABLE \n");
    print_scope_links();
    SymTable_free(symTable);
    free_scope_links();
    return 0;
}