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
    int called = 0;

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

program:            parsing      
                    ;
parsing:            stmt parsing 
                    | stmt 
                    ;

stmt:               expr SEMICOLON 
                    | ifstmt 
                    | whilestmt
                    | forstmt 
                    | returnstmt 
                    | KEYWORD_BREAK SEMICOLON {if(scope == 0) yyerror("Use of 'break' while not in a loop\n");}
                    | KEYWORD_CONTINUE SEMICOLON {if(scope == 0) yyerror("Use of 'continue' while not in a loop\n");}
                    | block 
                    | funcdef 
                    | SEMICOLON 
                    | error SEMICOLON   { yyerrok; }
                    ;

expr:                 expr '+' expr           
                    | expr '*' expr       
                    | expr '/' expr 
                    | expr '%' expr     
                    | expr GREATER expr   
                    | expr GREATER_EQUAL expr 
                    | expr LESS expr
                    | expr LESS_EQUAL expr   
                    | expr EQUALS expr        
                    | expr NOT_EQUAL expr 
                    | expr KEYWORD_AND expr 
                    | expr KEYWORD_OR expr   
                    | assignexpr            
                    | term 
                    ;


term:               LEFTPARENTHESIS expr RIGHTPARENTHESIS 
                    | '-' expr %prec UMINUS 
                    | KEYWORD_NOT expr 
                    | INCREMENT lvalue {entry=lookup($<stringv>1, scope); printf("scope %d", scope); if(!entry)return; if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
                    | lvalue INCREMENT {entry=lookup($<stringv>1, scope); printf("scope %d", scope);if(!entry)return; if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
                    | DECREMENT lvalue {entry=lookup($<stringv>1, scope); printf("scope %d", scope); if(!entry)return;if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
                    | lvalue DECREMENT  {entry=lookup($<stringv>1, scope); printf("scope %d", scope); if(!entry)return; else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
                    | primary 

assignexpr:         lvalue '=' expr {
    if(entry == NULL ) return;
    else if( entry->type == LIBFUNC || entry->type == USERFUNC) yyerror("Cannot assign to a function");
}
call:               IDENTIFIER callsuffix { called = 1; }
                    | call LEFTPARENTHESIS elist RIGHTPARENTHESIS
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call -> (funcdef)(elist)");}
                    ;
                    

primary:             call 
                    | lvalue 
                    | objectdef 
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  
                    | const
                    ;

lvalue:             IDENTIFIER {    
    
                                    if(called == 1){
                                        //checking for function call
                                        entry = lookup($1, scope);
                                        if(entry == NULL){
                                            yyerror("cannot call function");

                                        }else{
                                            if(!(entry->type == USERFUNC || entry->type == LIBFUNC)){
                                                yyerror("you are trying to call a nonfunction\n");
                                            }
                                        }
                                        called = 0;
                                        goto call_end;
                                    }

                                    int flag = 0;
                                    int tmp = scope;
                                    while(tmp >= 0 && flag == 0){
                                        entry = lookup($1, tmp);
                                        if(entry != NULL) flag = 1;
                                        tmp--;
                                    } 

                                    /*
                                    printf("Checking entry for %s\n  Scope: %d\n", $<stringv>1,scope);
                                    printf("Entry: %p", (void*)entry);
                                    */
                                    entry = lookup_in_scope($<stringv>1, scope);
                                     
                                    //if we dont find the identifier in any scope we add it to the st
                                    
                                    if(flag == 0){
                                        if (scope == 0) {
                                            entry = insert($1, GLOBAL, 0, yylineno);
                                        } else {
                                            entry = insert($1, LOCAL, scope, yylineno);
                                        }
                                    }
                                    if(entry!= NULL){
                                        entry = lookup($<stringv>1,scope);
                                        if(entry == NULL){
                                        }else if(entry->type == USERFUNC){
                                            break;
                                        }
                                        if(entry->type == LIBFUNC){
                                            yyerror("func collision at line \n");
                                        }
                                        else if(entry->type == USERFUNC) yyerror("program function collision \n");
                                                                           
                                    }else{
                                        printf("Cannot access %s at line %d\n",$<stringv>1,yylineno);
                                    }
                                    call_end:;
                                   
                                }

                    | KEYWORD_LOCAL IDENTIFIER {  
                                                int flag = 0;
                                                if(1){
                                                    entry = lookup($2, scope);

                                                    if(entry != NULL){
                                                        if(entry->type == LIBFUNC){
                                                            yyerror("Cannot shadow a library function");
                                    
                                                        }
                                                        else if(scope == 0){
                                                            yyerror("Cannot shadow a global variable");
                                                        }
                                                        else flag =1;
                                                        goto end;
                                                    }
                                                    else {
                                                        if(scope==0) yyerror("Cannot shadow a global variable");
                                                        else flag = 1;
                                                        goto end;

                                                    }
                                                }
                                                
                                                    
                                                       end:
                                                       if(flag == 1) {
                                                            entry = lookup_in_scope($2, scope);
                                                            if(entry == NULL) {
                                                                entry = insert($2, LOCAL, scope, yylineno);
                                                            }
                                                            else {
                                                                yyerror("Cannot shadow a local variable");
                                                            }
                                                       }                                                                                    
                                                        
                                                    
                                                }
                                            

                    | DOUBLECOLON IDENTIFIER   {
                                                    entry = lookup_in_scope($2, 0); 
                                                     
                                                        char error_message[256];
                                                        sprintf(error_message, "global identifier not found %s", $2);
                                                        if (entry == NULL || !entry->isActive) yyerror(error_message);
                                                }
                    | member

member:             lvalue DOT IDENTIFIER   { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error" );
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue.id");

                                            }            
                    | lvalue LEFTBRACKET expr RIGHTBRACKET { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue[expr]");
                                            }
                    | call DOT IDENTIFIER               
                    | call LEFTBRACKET expr RIGHTBRACKET


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

funcdef:            KEYWORD_FUNCTION  IDENTIFIER { 
                        if(scope <0  ) scope = 0;
                        entry = lookup_in_scope($2, scope); 
                     
                       //libfuncs
                        if (entry != NULL) {
                            //check collision with library/user functions or variables
                            if (entry->type == LIBFUNC) {
                                yyerror("library function collision");
                            } else if (entry->type == USERFUNC) {
                                yyerror("user function collision");
                            } else if (entry->type == FORMAL){
                                yyerror("formal collision");

                            }
                        }
                        else {
                            entry = insert($2, USERFUNC, scope, yylineno);
                            scope++;// increment scope here
                        }
                    } 
                    LEFTPARENTHESIS idlist RIGHTPARENTHESIS { scope--; }  block  
                    | KEYWORD_FUNCTION  { 
                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, scope, yylineno); 
                        scope++; // increment scope here
                    } 
                    LEFTPARENTHESIS idlist RIGHTPARENTHESIS { scope--; } block
                    ;

const:              number | STRING | KEYWORD_NIL | KEYWORD_TRUE | KEYWORD_FALSE

number:             INTEGER 
                    | REAL 
                    ;


idlist:              IDENTIFIER ids  {  
                                    
                                    entry = lookup($<stringv>1, scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }else if(strcmp($<stringv>1, entry->value.varVal->name) == 0) {
                                            yyerror("formal collision");
                                        }
                                    } else {
                                        entry = insert($<stringv>1,FORMAL,scope,yylineno);     
                                    }
                                }
                    | %empty                 {}
                    ;

ids:                COMMA IDENTIFIER  {  
                                    entry = lookup($<stringv>2, scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }
                                    } else {
                                        entry = insert($<stringv>2,FORMAL,scope,yylineno);     
                                    }
                                } ids
                    | %empty                 {}
                    ;

ifstmt:             KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt  KEYWORD_ELSE stmt 
                    | KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt 

whilestmt:          KEYWORD_WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS stmt 

forstmt:            KEYWORD_FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS stmt 

returnstmt:         KEYWORD_RETURN {if(scope == 0) yyerror("Use of 'return' while not in a loop\n");} expr  SEMICOLON 
                    | KEYWORD_RETURN {if(scope == 0) yyerror("Use of 'return' while not in a loop\n");} SEMICOLON 

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