%{
    #include <stdio.h>
    #include "quads.h"
    #include "stack.h"

    #define YYDEBUG 1
    #define BOLD_RED "\033[1;31m"
    #define RESET "\033[0m"

    Stack *scopeoffsetstack;

    extern int yydebug;
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);
    SymbolTableEntry *entry;
    SymbolTableEntry *sym;

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T symTable = NULL;
    int anonymousCounter = 0;
    int scope = 0;
    int called = 0;
    int doublec_flag = 0;
%}

%union{
    int intv;
    char* stringv;
    char charv;
    float floatv;
    struct SymbolTableEntry *sym;
    struct expr *expression;
    unsigned int unsignedv;
    //struct expr *index;
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


%type <stringv> program parsing stmt call callsuffix normcall methodcall elist exprlist objectdef obj indexed indexedelem block blockk number idlist ifstmt whilestmt forstmt returnstmt
%type <expression> term lvalue assignexpr expr primary  member const 
%type <stringv> funcname
%type <unsignedv> funcbody
%type <sym> funcprefix funcdef 


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

expr:                 expr '+' expr   {$$ = Manage_operations($1,add,$3);}
                    | expr '*' expr   {$$ = Manage_operations($1,mul,$3);}   
                    | expr '/' expr   {$$ = Manage_operations($1,divv,$3);}
                    | expr '%' expr   {$$ = Manage_operations($1,mod,$3);}  
                    | expr GREATER expr   {$$ = Manage_comparisonopers($1, ">",$3);}
                    | expr GREATER_EQUAL expr {$$ = Manage_comparisonopers($1, ">=",$3);}
                    | expr LESS expr  {$$ = Manage_comparisonopers($1, "<",$3);}
                    | expr LESS_EQUAL expr   {$$ = Manage_comparisonopers($1, "<=",$3);}
                    | expr EQUALS expr  {$$ = Manage_comparisonopers($1, "==",$3);}      
                    | expr NOT_EQUAL expr {$$ = Manage_comparisonopers($1, "!=",$3);}
                    | expr KEYWORD_AND expr 
                    | expr KEYWORD_OR expr   
                    | assignexpr            
                    | term 
                    ;


term:               LEFTPARENTHESIS expr RIGHTPARENTHESIS 
                    | '-' expr %prec UMINUS  {
                                                check_arith($2,(const char*)"- expr");
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp();
                                                emit(uminus,$2,NULL,$$,0,yylineno);
                                             }
                    | KEYWORD_NOT expr {
                                            $$ = newexpr(boolexpr_e);
                                            $$->sym = newtemp();
                                            emit(not,$2,NULL,$$,0,yylineno);
                                            
                                        }
                    | INCREMENT lvalue {entry=lookup($2, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
                    | lvalue INCREMENT {entry=lookup($1, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
                    | DECREMENT lvalue {entry=lookup($2, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
                    | lvalue DECREMENT {entry=lookup($1, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
                    | primary 

assignexpr:         lvalue  '='
 {
    if( entry == NULL ){
        if(scope > 0 )
        entry = lookup_hidden($1,scope);
        /* ERROR9.asc -> ACCESSING FORMAL IN ANOTHER SCOPE*/
        if(entry){
            if(entry->type == FORMAL){
                yyerror("cannot access formal argument in another scope");
            }else if(entry->type == LOCAL){
                yyerror("Cannot access local variable in another scope");
            }
        }else{
            if(scope==0){
                insert($1, GLOBAL, scope, yylineno);
            }else{
                insert($1, LOCAL, scope, yylineno);  
            }
        }
        
    }
    else if( entry->type == LIBFUNC || entry->type == USERFUNC) yyerror("Cannot assign to a function");

} 
expr {
    if($1->type == tableitem_e){
        emit(tablesetelem, $1, $1->index, $4, 0U, yylineno);
        $$ = emit_iftableitem($1);
        $$->type = assignexpr_e;
    }
    else{
        expr *temp = $4;
        emit(assign, $4, NULL, $1, 0U, yylineno);
        $$ = newexpr(assignexpr_e);
        $$->sym = newtemp();
        emit(assign, $1, NULL, $$, 0U, yylineno);
    }
} 



                    

primary:             lvalue {$$ = emit_iftableitem($1);}
                    | call 
                    | objectdef 
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  
                    | const
                    ;

lvalue:             IDENTIFIER          {    
                                                entry = lookup_in_scope($1, scope);                                                                                                // else if(entry->type == LIBFUNC) {
                                                //     yyerror("Cannot assign to a library function");
                                                // }
                                                // else if(entry->type == USERFUNC) {
                                                //     yyerror("Cannot assign to a user function");
                                                // }

                                                //phase3                                               
                                                //sym = lookup($1, scope);
                                                if(entry == NULL) {
                                                    entry = (scope == 0) ? insert($1, GLOBAL, 0, yylineno) : insert($1, LOCAL, scope, yylineno); 
                                                    entry->space = currscopespace();
                                                    entry->offset = currscopeoffset();
                                                    inccurrscopeoffset();
                                                }
                                                $$->sym = entry;
                                                $$ = lvalue_expr(entry);
                                                $$->strConst = yylval.stringv;
                                            
                                        }   

                    | KEYWORD_LOCAL IDENTIFIER {  
                                                    int flag = 0;                                               
                                                    entry = lookup($2, scope);
                                                    if(entry != NULL){
                                                        if(entry->type == LIBFUNC) yyerror("Cannot shadow a library function");                                                                      
                                                        // else if(scope == 0){
                                                        //     yyerror("Cannot shadow a global variable");
                                                        // }
                                                        else flag =1;
                                                        goto end;
                                                    }
                                                    else {
                                                        //if(scope==0) yyerror("Cannot shadow a global variable");
                                                        flag = 1;
                                                        goto end;
                                                    }
                                                
                                                    end:
                                                    if(flag == 1) {
                                                        entry = lookup_in_scope($2, scope);
                                                        if(entry == NULL) entry = insert($2, LOCAL, scope, yylineno);                                                   
                                                        else yyerror("Cannot shadow a local variable"); 
                                                    }

                                                    //phase 3
                                                    sym = lookup_in_scope($2, scope);
                                                    if (sym == NULL){
                                                        sym = (scope == 0) ? insert($2, GLOBAL, 0, yylineno) : insert($2, LOCAL, scope, yylineno); 
                                                        sym->space = currscopespace();
                                                        sym->offset = currscopeoffset();
                                                        inccurrscopeoffset();
                                                    } else {
                                                        if(sym->type == USERFUNC || sym->type == LIBFUNC ){
                                                            printf(BOLD_RED"sym is a function\n"RESET);
                                                        }

                                                    }
                                                    $$ = lvalue_expr(sym);                                                                                                                                      
                                                    
                                                }
                                            

                    /*WORKS FOR ::f() BUT NOT FOR :f(f()) or (functiondef)(elist)*/
                    | DOUBLECOLON IDENTIFIER callsuffix {
                                                            entry = lookup_in_scope($2, 0); 
                                                            if(entry == NULL) yyerror("global identifier not found");
                                                            
                                                        }
                    
                    
                    | DOUBLECOLON IDENTIFIER   {
                                                    entry = lookup_in_scope($2, 0); 
                                            
                                                        char error_message[256];
                                                        sprintf(error_message, "global identifier not found %s", $2);
                                                        if (entry == NULL || !entry->isActive) yyerror(error_message);

                                                }
                    | member {$$ = $1;}

member:             lvalue DOT IDENTIFIER   { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error" );
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue.id");
                                            $$ = member_item($1, $3);
                                            }            
                    | lvalue LEFTBRACKET expr RIGHTBRACKET { 
                                            expr* tmp;
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue[expr]");
                                            $1 = emit_iftableitem($1);
                                            tmp = newexpr(tableitem_e);
                                            tmp->sym = $1->sym;
                                            tmp->index = $3;
                                            $$ = tmp;
                                            }
                    | call DOT IDENTIFIER               
                    | call LEFTBRACKET expr RIGHTBRACKET
                    ;

call:               call LEFTPARENTHESIS elist RIGHTPARENTHESIS 
                    | IDENTIFIER callsuffix {
                                                // int temp = scope-1;
                                                // while(temp >= 0){
                                                //     entry = lookup_in_scope($1, temp);
                                                //     if(entry != NULL) break;
                                                //     temp--;
                                                // }
                                                // if(entry == NULL) yyerror("Cannot call function");
                                                // else if(entry->type != LIBFUNC || entry->type != USERFUNC) yyerror("not a function");
                    }
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call -> (funcdef)(elist)");}
                    ;

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
             

objectdef:          LEFTBRACKET  elist RIGHTBRACKET
                    | LEFTBRACKET indexed RIGHTBRACKET
                    | LEFTBRACKET RIGHTBRACKET
                    ;

obj:                elist 
                    | indexed 
                    ;
                    
indexed:            indexedelem 
                    | indexedelem COMMA indexed
                    ;

indexedelem:        LEFTBRACE expr COLON expr RIGHTBRACE 

block:              LEFTBRACE  { scope++; } blockk  RIGHTBRACE { scope--; }
                    ;

blockk:              stmt blockk
                    | %empty            {}
                    ;

funcname: IDENTIFIER {
                        
                        if(scope < 0) scope = 0;
                        entry = lookup_in_scope($1, scope); 

                        int temp = scope;
                        while(temp >= 0){
                            hide_scope(temp);
                            temp--;
                        }
                     
                       //libfuncs
                        if (entry != NULL) {
                            //check collision with library/user functions or formals
                            if (entry->type == LIBFUNC) yyerror("library function collision");
                            else if (entry->type == USERFUNC) yyerror("user function collision");
                            else if (entry->type == FORMAL) yyerror("function name already defined as formal");
                            
                        }
                        else {
                            //entry = lookup_in_scope_hidden($<stringv>2, scope);
                            //if(!entry) yyerror("variable already defined"); 
                            //else{ 
                                entry = insert($1, USERFUNC, scope, yylineno);
                                scope++;
                            //} 
                        }

                        $$ = entry->value.funcVal;
                    } 

funcname: %empty  { 
                        int temp = scope;
                        printf("scope %d\n", scope);
                        while(temp != 0){
                        hide_scope(temp);
                        temp--;
                        }

                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, scope, yylineno); 
                        scope++; // increment scope here

                        $$ = entry;
                    } 

funcprefix: KEYWORD_FUNCTION funcname {
                                        $$ = insert($2, USERFUNC, scope, yylineno);
                                        $$->iaddress = nextquadlabel();
                                        emit(funcstart, lvalue_expr($$), NULL, NULL, $$->iaddress, yylineno);
                                        push(scopeoffsetstack, currscopeoffset());
                                        enterscopespace();
                                        resetformalargsoffset();
                                       }  




funcargs: LEFTPARENTHESIS idlist RIGHTPARENTHESIS {
                                                     scope--;
                                                     enterscopespace();
                                                     resetfunctionlocalsoffset();
                                                  } 
funcbody: block {
                 $$ = currscopeoffset();
                 exitscopespace();
                 //slide 6 mathima 10
                }

funcdef:   funcprefix funcargs funcbody  {
                                            exitscopespace();
                                            $$->totalLocals = $3;
                                            int offset = pop(scopeoffsetstack);
                                            restorecurrscopeoffset(offset);
                                            $$ = $1;
                                            emit(funcend, lvalue_expr($1), NULL, NULL, $1->iaddress + yylineno, yylineno);

}                         
           ;

const:              number                  
                    | STRING                { $$ = newexpr_conststring(yylval.stringv); }
                    | KEYWORD_NIL           { $$ = newexpr_nil(yylval.stringv);  }
                    | KEYWORD_TRUE          { 
                                              $$ = newexpr_bool(yylval.stringv);
                                            }
                    | KEYWORD_FALSE         { $$ = newexpr_bool(yylval.stringv); }

number:             INTEGER                 { $$ = newexpr_constnum(yylval.intv); }
                    | REAL                  { $$ = newexpr_constnum(yylval.floatv); }
                    ;


idlist:              IDENTIFIER ids  {  
                                    
                                    entry = lookup($<stringv>1, scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
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
                                        }else if(strcmp($<stringv>1, entry->value.varVal->name) == 0) {
                                            yyerror("formal collision");
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
    
    scopeoffsetstack = malloc(sizeof(Stack));
    if (scopeoffsetstack == NULL) {
        fprintf(stderr, "Failed to allocate memory for scopeoffsetstack\n");
        return 1;
    }
    initialize(scopeoffsetstack);

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

    printf("PRINTING QUADS\n");
    print_quads();

    SymTable_free(symTable);
    free_scope_links();
    return 0;
}