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

assignexpr:         lvalue '=' expr {printf("assignexpr -> lvalue = expr");}

primary:            lvalue {printf("primary -> lvalue");}
                    | call {printf("primary -> call");}
                    | objectdef {printf("primary -> objectdef");}
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  {printf("primary -> (funcdef)");}
                    | const {printf("primary -> const");}

lvalue:             IDENTIFIER {
                                    entry = lookup($1, scope); 
                                    if (entry != NULL) {
                                        if (!entry->isActive) {
                                            yyerror("identifier error");
                                        }
                                    } else {
                                        if (scope == 0) {
                                            entry = insert($1, GLOBAL, 0, yylineno);
                                        } else {
                                            entry = insert($1, LOCAL, scope, yylineno);
                                        }
                                    }
                                }

                    | KEYWORD_LOCAL IDENTIFIER {  
                                                    entry = lookup($2, scope); 
                                                    if (entry != NULL) {
                                                        if (!entry->isActive) {
                                                            yyerror("local identifier error");
                                                        }
                                                    } else {
                                                        entry = insert($2, LOCAL, ++scope, yylineno);
                                                    }
                                                }

                    | DOUBLECOLON IDENTIFIER   {
                                                    entry = lookup($2, 0); 
                                                    if (entry == NULL || !entry->isActive) {
                                                        yyerror("global identifier error");
                                                    } else {
                                                        entry = insert($2, GLOBAL, 0, yylineno);
                                                    }
                                                }
                    | member

member:             lvalue DOT IDENTIFIER  {printf("member -> lvalue.IDENTIFIER");}             
                    | lvalue LEFTBRACKET expr RIGHTBRACKET {printf("member -> lvalue[expr]");}
                    | call DOT IDENTIFIER {printf("member -> call.IDENTIFIER");}              
                    | call LEFTBRACKET expr RIGHTBRACKET {printf("member -> call[expr]");}

call:               call LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call -> call(elist)");}
                    | lvalue callsuffix {printf("call -> lvalue callsuffix");}
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call -> (funcdef)(elist)");}

callsuffix:         normcall {printf("callsuffix -> normcall");}
                    | methodcall {printf("callsuffix -> methodcall");}

normcall:           LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("normcall -> (elist)");}

methodcall:         DOUBLECOLON IDENTIFIER LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("methodcall -> ::IDENTIFIER(elist)");}

elist:              exprlist {printf("elist -> exprlist");}
                    | %empty            {}
                    ;

exprlist:           exprlist  COMMA expr {printf("exprlist -> exprlist,expr");}
                    | expr {printf("exprlist -> expr");}
                    ;
             

objectdef:          LEFTBRACKET  obj RIGHTBRACKET  {printf("objectdef -> [obj]");}
                    ;

obj:                elist {printf("obj -> elist");}
                    | indexed {printf("obj -> indexed");}
                    ;
                    
indexed:            indexedelem  COMMA indexedelem  {printf("indexed -> indexedelem,indexedelem");}
                    | indexedelem {printf("indexed -> indexedelem");}
                    ;

indexedelem:        LEFTBRACE expr COLON expr RIGHTBRACE {printf("indexedelem -> {expr:expr}");}

block:              LEFTBRACE  { scope++; } blockk  RIGHTBRACE { scope--; }
                    ; 

blockk:              stmt blockk {printf("blockk -> stmt blockk");}
                    | %empty            {}
                    ;

funcdef:            KEYWORD_FUNCTION  IDENTIFIER {  entry = insert($2,USERFUNC,0,yylineno);   } LEFTPARENTHESIS idlist RIGHTPARENTHESIS block {
    
                        entry = lookup_in_scope($2, scope); 
                        if (entry != NULL) {yyerror("Function redefinition error");} else {
                            entry = insert($2, USERFUNC, scope, yylineno);
                            scope++;
                        }
    }     
                    | KEYWORD_FUNCTION  { 
                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, 0, yylineno); 
                        scope++;
                        } 
                        LEFTPARENTHESIS idlist RIGHTPARENTHESIS block          
                    ;
const:              number | STRING | KEYWORD_NIL | KEYWORD_TRUE | KEYWORD_FALSE

number:             INTEGER {printf("number -> INTEGER");}
                    | REAL {printf("number -> REAL");}
                    ;
idlist:             IDENTIFIER COMMA idlist                                                        {  entry = insert($1,FORMAL,0,yylineno);   }
                    | IDENTIFIER                                                                    {  entry = insert($1,FORMAL,0,yylineno);   }
                    | %empty                                                                        {}
                    ;

ifstmt:             KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt  KEYWORD_ELSE stmt  {printf("ifstmt -> if(expr)stmt else stmt");}
                    | KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt {printf("ifstmt -> if(expr)stmt");}

whilestmt:          KEYWORD_WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt {printf("whilestmt -> while(expr)stmt");}

forstmt:            KEYWORD_FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS stmt {printf("forstmt -> for(elist;expr;elist)stmt");}

returnstmt:         KEYWORD_RETURN  expr  SEMICOLON {printf("returnstmt -> return expr;");}
                    | KEYWORD_RETURN SEMICOLON {printf("returnstmt -> return;");}

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