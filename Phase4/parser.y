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
    reversed_list *rev_list = NULL;
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T symTable = NULL;
    int anonymousCounter = 0;
    int scope = 0;
    int called = 0;
    int doublec_flag = 0;
    void backpatchor(int list, int label);
    void backpatchand(int list, int label);

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
    struct reversed_list *call_list;
    struct call *calls;
    struct for_struct *for_stmt;
    struct stmt_struct *stmt_structt;
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



%type <stringv> program parsing  number whilestmt forstmt 
%type <expression>elist elist_help term lvalue assignexpr expr primary  member const call  exprlist   returnstmt  objectdef obj indexed indexedelem indexedelem_list


%type <unsignedv> funcbody  whilestart whilecond N M ifprefix elseprefix
%type <sym> funcprefix funcdef funcname idlist ids funcargs
%type <calls> callsuffix normcall methodcall 
%type <for_stmt> forprefix
%type <stmt_structt> stmt ifstmt stmts block  loopstmt loopstart loopend 

%right '='
%left KEYWORD_OR
%left KEYWORD_AND
%nonassoc EQUALS NOT_EQUAL
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL 
%left '+' '-'
%left '*' '/' '%'
%right KEYWORD_NOT INCREMENT DECREMENT UMINUS
%left DOT DOUBLEDOT
%left LEFTBRACKET RIGHTBRACKET
%left LEFTPARENTHESIS RIGHTPARENTHESIS 


%%

program:            stmts      
                    ;
// parsing:            stmt parsing { $$ = $1; }
//                     | %empty            {} 
//                     ;

stmts:              stmt stmts{ 
                        $$ = make_stmt();
                        $$->breaklist = mergelist($1->breaklist, $2->breaklist);
                        $$->contlist = mergelist($1->contlist, $2->contlist);
                    }
                    | %empty { $$ = make_stmt(); }
                    ;

stmt:               expr SEMICOLON  {//printf("reset\n");
                                    $$ = make_stmt();
                                    expr *temp = $1;
                                    backpatching(temp);
                                     
                                     resettemp();
                                    }
                    | ifstmt        { resettemp(); $$=$1;}
                    | whilestmt     {$$ = make_stmt();resettemp();}
                    | forstmt       {$$ = make_stmt();resettemp();}
                    | returnstmt    {$$ = make_stmt(); resettemp();}
                    | KEYWORD_BREAK SEMICOLON {if(scope == 0) yyerror("Use of 'break' while not in a loop\n");
                                                $$ = $1;
                                                struct stmt_struct* t = make_stmt();
                                                t->breaklist = newlist(nextquadlabel()-1);
                                                emit(jump, NULL, NULL, NULL, 0, yylineno);
                                                $$ = t;
                                                resettemp();}
                    | KEYWORD_CONTINUE SEMICOLON {if(scope == 0) yyerror("Use of 'continue' while not in a loop\n");
                                                $$=$1;
                                                stmt_struct* t = make_stmt();
                                                emit(jump, NULL, NULL, NULL, 0, yylineno);
                                                t->contlist = newlist(nextquadlabel()-1);
                                                $$ = t;
                                                resettemp();}
                                                
                    | block { $$ = $1;   resettemp(); printf("enter stmt");}
                    | funcdef { resettemp();}
                    | SEMICOLON {$$ = make_stmt(); resettemp();}
                    | error SEMICOLON   { yyerrok; }
                    ;


expr:                 expr '+' expr   {$$ = Manage_operations($1,add,$3);}
                    | expr '*' expr   {$$ = Manage_operations($1,mul,$3);}   
                    | expr '-' expr   {$$ = Manage_operations($1,sub,$3);}   
                    | expr '/' expr   {$$ = Manage_operations($1,divv,$3);}
                    | expr '%' expr   {$$ = Manage_operations($1,mod,$3);}  
                    | expr GREATER expr   {$$ = Manage_comparisonopers($1, ">",$3);}
                    | expr GREATER_EQUAL expr {$$ = Manage_comparisonopers($1, ">=",$3);}
                    | expr LESS expr  {$$ = Manage_comparisonopers($1, "<",$3);}
                    | expr LESS_EQUAL expr   {$$ = Manage_comparisonopers($1, "<=",$3);}
                    | expr EQUALS expr  {$$ = Manage_comparisonopers($1, "==",$3);}      
                    | expr NOT_EQUAL expr {$$ = Manage_comparisonopers($1, "!=",$3);}
                    | expr KEYWORD_AND {
                        if($1->type != boolexpr_e){
                            expr *temp = newexpr(boolexpr_e);
                            //temp->sym = newtemp();
                            emit(if_eq, $1, newexpr_constbool(1), NULL, nextquadlabel(), yylineno);
                            emit(jump, NULL, NULL, NULL, nextquadlabel(), yylineno);
                            temp->truelist = newlist(nextquadlabel()-2);
                            temp->falselist = newlist(nextquadlabel()-1);
                            // patchlist(temp->falselist, nextquadlabel()+1);
                            $1 = temp;
                        }
                    } M expr { 
                        if($5->type != boolexpr_e){
                            expr *temp = newexpr(boolexpr_e);
                            //temp->sym = newtemp();
                   
                            emit(if_eq, temp, newexpr_constbool(1), NULL, nextquadlabel(), yylineno);
                            emit(jump, NULL, NULL, NULL, nextquadlabel(), yylineno);
                            temp->truelist =newlist(nextquadlabel()-2);
                            temp->falselist = newlist(nextquadlabel()-1);
                            $5 = temp;
                        }
                        $$ = newexpr(boolexpr_e);
                        //$$->type = boolexpr_e;
                        patchlist($1->truelist, $4+1);
                        $$->truelist = $5->truelist;
                        $$->falselist = mergelist($1->falselist, $5->falselist);
                        backpatchand($1->falselist, nextquadlabel()+1);
                    }
                    | expr KEYWORD_OR {
                        if($1->type != boolexpr_e){
                            expr *temp = newexpr(boolexpr_e);
                            //temp->sym = newtemp();  
                            emit(if_eq, $1, newexpr_constbool(1), NULL, nextquadlabel(), yylineno);
                            emit(jump, NULL, NULL, NULL, nextquadlabel(), yylineno);
                            $1 = temp;
                            temp->truelist =newlist(nextquadlabel()-2);
                            temp->falselist = newlist(nextquadlabel()-1);
                        }
                    } M expr { 
                        if($5->type != boolexpr_e){
                            expr *temp = newexpr(boolexpr_e);
                            //temp->sym = newtemp();
                            
                            emit(if_eq, $5, newexpr_constbool(1), NULL, nextquadlabel(), yylineno);
                            emit(jump, NULL, NULL, NULL, nextquadlabel(), yylineno);
                            $5 = temp;
                            temp->truelist =newlist(nextquadlabel()-2);
                            temp->falselist = newlist(nextquadlabel()-1);
                        }
                        $$ = newexpr(boolexpr_e);
                        //$$->type = boolexpr_e;
                        patchlist($1->falselist, $4);
                        $$->falselist = $5->falselist;
                        $$->truelist = mergelist($1->truelist, $5->truelist);
                        backpatchor($1->truelist, nextquadlabel());
                        
                    } 
                    | assignexpr { $$ = $1;}        
                    | term  { $$ = $1;}
                    ;


term:               LEFTPARENTHESIS expr RIGHTPARENTHESIS   {$$ = $2;}
                    | '-' expr %prec UMINUS  {
                                                check_arith($2,(const char*)"- expr");
                                                $$ = newexpr(arithexpr_e);
                                                $$->sym = newtemp();
                                    
                                                emit(uminus,$2,NULL,$$,0,yylineno);
                                             }
                    | KEYWORD_NOT expr {
                                            $$ = newexpr(boolexpr_e);
                                            $$->sym = newtemp();
                                            true_test($2);
                                            unsigned int tmp = $2->truelist;
                                            $2->truelist =$2->falselist;
                                            $2->falselist = tmp;
                                            $$ = $2;
                                            //emit(not,$2,NULL,$$,0,yylineno);
                                            
                                        }
                    | INCREMENT lvalue {entry=lookup($2, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");
                                        check_arith($2,(const char*)"lvalue++");
                                        if($2->type == tableitem_e){
                                            $$ = emit_iftableitem($2);
                                            emit(add, $$, newexpr_constnum(1), $$, 0U, yylineno);
                                            emit(tablesetelem, $2->index, $$, $2, 0U, yylineno);
                                        }else{
                                            expr *temp = newexpr(arithexpr_e);
                                            temp->sym = newtemp();
                                            emit(add, $2, newexpr_constnum(1), $2, 0U, yylineno);
                                            emit(assign, $2, NULL, temp, 0U, yylineno);
                                        }
                                        }
                    | lvalue INCREMENT {entry=lookup($1, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");
                                        check_arith($1,(const char*)"++lvalue");
                                        expr *tmp = NULL;
                                        tmp = newexpr(arithexpr_e);
                                        tmp->sym = newtemp();
                                        if($1->type == tableitem_e){
                                            expr *v = emit_iftableitem($1);
                                            emit(assign, v, NULL, tmp, 0U, yylineno);
                                            emit(add, v, newexpr_constnum(1), v, 0U, yylineno);
                                            emit(tablesetelem, $1->index, v, $1, 0U, yylineno);
                                        }else {
                                            emit(assign, $1, NULL, tmp, 0U, yylineno);
                                            emit(add, $1, newexpr_constnum(1), $1, 0U, yylineno);
                                        }

                                        }
                    | DECREMENT lvalue {entry=lookup($2, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");
                                        check_arith($2,(const char*)"lvalue--");
                                        if($2->type == tableitem_e){
                                            $$ = emit_iftableitem($2);
                                            emit(sub, $$, newexpr_constnum(1), $$, 0U, yylineno);
                                            emit(tablesetelem, $2->index, $$, $2, 0U, yylineno);
                                        } else {
                                            expr *temp = newexpr(arithexpr_e);
                                            temp->sym = newtemp();
                                            emit(sub, $2, newexpr_constnum(1), $2, 0U, yylineno);
                                            emit(assign, $2, NULL, temp, 0U, yylineno);
                                        }
                                        }
                    | lvalue DECREMENT {entry=lookup($1, scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");
                                        check_arith($1,(const char*)"--lvalue");
                                        expr *tmp = NULL;
                                        tmp = newexpr(arithexpr_e);
                                        tmp->sym = newtemp();
                                        if($1->type == tableitem_e){
                                            expr *v = emit_iftableitem($1);
                                            emit(assign, v, NULL, tmp, 0U, yylineno);
                                            emit(sub, v, newexpr_constnum(1), v, 0U, yylineno);
                                            emit(tablesetelem, $1->index, v, $1, 0U, yylineno);
                                        }
                                        else {
                                            emit(assign, $1, NULL, tmp, 0U, yylineno);
                                            emit(sub, $1, newexpr_constnum(1), $1, 0U, yylineno);                   }
                                        
                                        }
                    | primary { $$ = $1; }

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
        emit(tablesetelem, $1->index, $1, $4, 0U, yylineno+2000);
        $$ = emit_iftableitem($1);
        $$->type = assignexpr_e;
    }
    else{
        expr *temp = $4;
        if($4->type == boolexpr_e){
            temp = backpatching($4);
        } 
        emit(assign, temp, NULL, $1, 0U, yylineno);
        temp = newexpr(assignexpr_e);
        temp->sym = newtemp();
        emit(assign, $1, NULL,temp, 0U, yylineno);
        $$ = temp;
    }
} 

primary:             lvalue {$$ = emit_iftableitem($1);}
                    | call 
                    | objectdef 
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  
                    | const {$$ = $1;}
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
                                                $$ = lvalue_expr(entry);
                                                $$->sym = entry;

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
                                            

                    // /*WORKS FOR ::f() BUT NOT FOR :f(f()) or (functiondef)(elist)*/
                    // BIG PROBLEM IF UNCOMMENTED ABOVE ISSUE IS FIXED , BUT 4 SHIFT/REDUCe CONFLICTS
                    // | DOUBLECOLON IDENTIFIER callsuffix {
                    //                                         entry = lookup_in_scope($2, 0); 
                    //                                         if(entry == NULL) yyerror("global identifier not found");
                                                            
                    //                                     }
                    
                    
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
call:               call LEFTPARENTHESIS elist RIGHTPARENTHESIS  { $$ =  make_call($1,$3);}
                    | lvalue callsuffix 
                                            {
                                                $1 = emit_iftableitem($1);
                                                if($2 && $2->method){
                                                    expr *last = $1;

                                                    $1 = emit_iftableitem(member_item(last,$2->name));
                                                    expr *temp = $2->elist;
                                                        if(temp==NULL)
                                                              {
                                                                $2->elist=last;
                                                              }
                                                              else
                                                              {

                                                                while(temp->next!=NULL)
                                                                {
                                                                    temp=temp->next;
                                                                }
                                                                temp->next=last;
                                                              }
                                                }
                                                $$ = make_call($1,$2->elist);
                                            }
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS 
                                                                                                            { 
                                                                                                                expr* func = newexpr(programfunc_e);
                                                                                                                if($2 !=NULL)
                                                                                                                func->sym = $2;
                                                                                                                $$ = make_call(func,$5);
                                                                                                            }
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS  RIGHTPARENTHESIS 
                                                                                                            { 
                                                                                                                expr* func = newexpr(programfunc_e);
                                                                                                                if($2 !=NULL)
                                                                                                                func->sym = $2;
                                                                                                                $$ = make_call(func,NULL);
                                                                                                            }
                    | LEFTPARENTHESIS RIGHTPARENTHESIS 
                                                        {
                                                            $$ = make_call($$,NULL);
                                                        }
                    ;


callsuffix:         normcall  
                                {
                                    $$ = malloc(sizeof(calls));
                                    $$ = $1;
                                }
                    | methodcall {
                                    $$ = malloc(sizeof(calls));
                                    $$ = $1;
                                }

normcall:           LEFTPARENTHESIS elist RIGHTPARENTHESIS  
                                                            {
                                                                $$ = malloc(sizeof(calls));
                                                                $$->elist = $2;
                                                                $$->method = 0;
                                                                $$->name = NULL;
                                                            }

methodcall:         DOUBLEDOT IDENTIFIER LEFTPARENTHESIS elist RIGHTPARENTHESIS  
                                                                                {
                                                                                    $$->elist = $4;
                                                                                    $$->method = 1;
                                                                                    $$->name = strdup($2);
                                                                                }

// elist_help:         COMMA expr elist_help
//                                             {
//                                                 expr * temp = $2;
                                        
//                                                 printf("temp->type %d\n", temp->type);
//                                                 printf("temp->sym %s\n", temp->sym->value.varVal->name);
//                                                 addToExprList(&$3,$2);
//                                                 printf("before $$ b is? %s\n", $3->item->sym->value.varVal->name);
//                                                 $$ = $3;
//                                                 printf("after $$ b is? %s\n", $$->item->sym->value.varVal->name);
//                                             }
//                     | {$$ = NULL;}


elist:              expr { 
                            if($1->type == boolexpr_e){
                                $1 = backpatching($1);
                            }
                            $$ = $1;
                            }   
                    |expr COMMA elist{
                              
                                if($1->type == boolexpr_e){
                                    $1 = backpatching($1);
                                }
                                if($1 != NULL){
                                    $1->next = $3;
                                }
                                // printf("expr a %s and expr b %s\n", $$->next->item->sym->value.varVal->name,$$->next->next->item->sym->value.varVal->name);
                                }
                    | %empty { $$ = NULL;}
                    ;

objectdef:          LEFTBRACKET  elist RIGHTBRACKET {
													int count = 0;
													expr* t = newexpr(newtable_e);
													t->sym = newtemp();
													emit(tablecreate, (expr*) 0, (expr*) 0, t, currQuad, yylineno);
													while($2 != NULL){
														emit(tablesetelem, t, newexpr_constnum(count++), $2, currQuad, yylineno+1000);
														$2 = $2->next;
													}
													$$ = t;
												}
                    | LEFTBRACKET indexed RIGHTBRACKET{
													expr* t = newexpr(newtable_e);
													t->sym = newtemp();
													emit(tablecreate, (expr*) 0, (expr*) 0, t, currQuad, yylineno);
													while($2!=NULL){
														emit(tablesetelem, t, $2->index, $2, currQuad, yylineno+1000);
														$2 = $2->next;
													}
													$$ = t;		
												}
                    
                    ;

obj:                elist 
                    | indexed 
                    ;
                    
indexed:            indexedelem indexedelem_list {$$=$1; $$->next=$2;}
                    ;

indexedelem_list: COMMA indexedelem indexedelem_list {$$=$2;$$->next=$3;}
                    |%empty {$$ = NULL;}
                    ;

indexedelem:        LEFTBRACE expr COLON expr RIGHTBRACE {$$=$4;$$->index=$2;}
                    ;
block:              LEFTBRACE { scope++; } stmts RIGHTBRACE { 
                                                                scope--; 
                                                                $$ = make_stmt(); 
                                                                printf("enter block");
                                                            }
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
                        $$ = entry;
                        $$->value.funcVal->name = entry->value.funcVal->name;
                    } 

funcname: %empty  { 
                        int temp = scope;
                        while(temp != 0){
                        hide_scope(temp);
                        temp--;
                        }

                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, scope, yylineno); 
                        scope++; // increment scope here

                        $$ = entry;
                        $$->value.funcVal->name = entry->value.funcVal->name;

                    } 

funcprefix: KEYWORD_FUNCTION funcname {
                                        $$ = $2;
                                        $$->iaddress = nextquadlabel();

                                        emit(jump, NULL, NULL, NULL, 0, yylineno);
                                        emit(funcstart, lvalue_expr($$), NULL, NULL,0, yylineno);
                                        push(scopeoffsetstack, currscopeoffset());
                                        print(scopeoffsetstack);
                                        enterscopespace();
                                        resetformalargsoffset();
                                       }  




funcargs: LEFTPARENTHESIS idlist RIGHTPARENTHESIS {
                                                     scope--;
                                                     enterscopespace();
                                                     resetfunctionlocalsoffset();
                                                     $$ = $2;
                                                  } 
funcbody: block {
                 $$ = currscopeoffset();
                 exitscopespace();
                 //slide 6 mathima 10
                }

funcdef:   funcprefix funcargs funcbody  {
                                            exitscopespace();
                                            $$->totalLocals = $3;
                                            print(scopeoffsetstack);
                                            int offset = pop(scopeoffsetstack);
                                            restorecurrscopeoffset(offset);
                                            $$ = $1;
                                            SymbolTableEntry *temp = $1;

                                            emit(funcend, lvalue_expr($1), NULL, NULL, 0U, yylineno);
                                            patchlabel($1->iaddress, nextquadlabel());


}                         
           ;

const:              number                  
                    | STRING                { $$ = newexpr_conststring(yylval.stringv); }
                    | KEYWORD_NIL           {$$ = newexpr_nil();}
                    | KEYWORD_TRUE          { 
                                              $$ = newexpr_constbool(1);
                    
                                            }
                    | KEYWORD_FALSE         { $$ = newexpr_constbool(0); }

number:             INTEGER                 { $$ = newexpr_constnum(yylval.intv); }
                    | REAL                  { $$ = newexpr_constnum(yylval.floatv); }
                    ;


idlist:              IDENTIFIER ids  {  
                                    entry = lookup($1, scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }
                                    } else {  
                                        entry = insert($<stringv>1,FORMAL,scope,yylineno);     
                                    }
                                    $$ = $1;

                                }
                    | %empty                 {}
                    ;

ids:                COMMA IDENTIFIER  {  
                                    printf("scope is %d\n", scope);

                                    entry = lookup(yylval.stringv, scope); //lookup in function scope
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


ifprefix:           KEYWORD_IF LEFTPARENTHESIS expr RIGHTPARENTHESIS {
                                                            if($3->type == boolexpr_e) {
                                                                $3 = backpatching($3);
                                                            }
                                                            printf("cq %d\n", currQuad);
                                                            emit(if_eq,$3,newexpr_constbool(1),NULL,currQuad+3,yylineno);
                                                            printf("cq %d\n", currQuad);
                                                            $$ = currQuad;
                                                            emit(jump,NULL,NULL,NULL,0U,yylineno);
                                                            
                                                        }
                                                    ;

elseprefix:         KEYWORD_ELSE {
                                    $$ = currQuad;
                                    emit(jump,NULL,NULL,NULL,0,yylineno);
                                }
                    ;                                                    

ifstmt:             ifprefix stmt elseprefix stmt {
                                                   
                                                    patchlabel($1, $3 + 1);
                                                    patchlabel($3, currQuad);
                                                    $2 = malloc(sizeof(struct stmt_struct));
                                                    $4 = malloc(sizeof(struct stmt_struct));
                                                    $2->breaklist = 0;
                                                    $2->contlist = 0;
                                                    $4->breaklist = 0;
                                                    $4->contlist = 0;
                                                    stmt_struct* t = make_stmt();
                                                    
                                                    t->breaklist = $2->breaklist ? ($4->breaklist ? mergelist($2->breaklist, $4->breaklist) : $2->breaklist) : $4->breaklist;
                                                    t->contlist = $2->contlist ? ($4->contlist ? mergelist($2->contlist, $4->contlist) : $2->contlist) : $4->contlist;
                                                    //printf("breaklist %d\n", t->breaklist);
                                                   
                                                    $$ = t;
                                                   
                                                    //free($2);
                                                    //free($4);
                                                }
                                                
                    | ifprefix stmt {  
                                        
                                        patchlabel($1, currQuad);
                                        $$ = $2;
                                    }
                    ;

loopstart:%empty  {++loopcounter;}

loopend:%empty  {--loopcounter;}

loopstmt: loopstart stmt loopend { $$ =$2;}                    


whilestart: KEYWORD_WHILE 
                            {
                              $$ = nextquadlabel();  
                            }
            ;

whilecond: LEFTPARENTHESIS expr RIGHTPARENTHESIS
                                                    {
                                                        if($2->type == boolexpr_e){
                                                            $2 = backpatching($2);
                                                        }
                                                        emit(if_eq,$2,newexpr_constbool(1),NULL,nextquadlabel()+3,yylineno);
                                                        $$ = nextquadlabel();
                                                        emit(jump,NULL,NULL,NULL,0U,yylineno);
                                                        
                                                    }
            ;

whilestmt:          whilestart whilecond stmt 
                                                {
                                                    
                                                    $3 = malloc(sizeof(struct stmt_struct));
                                                    $3->breaklist = 0;
                                                    $3->contlist = 0;
                                                    emit(jump,NULL,NULL,$1,1,yylineno);
                                                    patchlabel($2, nextquadlabel());
                                                    patchlist($3->breaklist, nextquadlabel());
                                                    patchlist($3->contlist, $1);
                                                }
                    ;

N: %empty {$$ = nextquadlabel(); emit(jump,NULL,NULL,NULL,0U,yylineno);}
M: %empty {$$ = nextquadlabel();}

forprefix:  KEYWORD_FOR LEFTPARENTHESIS elist SEMICOLON M expr SEMICOLON
            {
                $$->test = $5;
                $$->enter = nextquadlabel();
                emit(if_eq,$6,newexpr_constbool(1),NULL,0U,yylineno);
            }
            ;
forstmt:            forprefix N elist RIGHTPARENTHESIS N stmt N 
                    {
                        // $6 = malloc(sizeof(stmt_struct));
                        patchlabel($1->enter, $5+1); //true jump
                        patchlabel($2, nextquadlabel()); // false jump
                        patchlabel($5, $1->test); // loop jump
                        patchlabel($7, $2+1); // closure jump
                        patchlist($6->breaklist, nextquadlabel());
                        patchlist($6->contlist, $2+1);
                    }
                    ;

returnstmt:         KEYWORD_RETURN expr  SEMICOLON {
                                                    if(scope == 0) yyerror("Use of 'return' while not in a function\n");
                                                    emit(ret, NULL, NULL, $2, 0, yylineno);
                                                    emit(jump, NULL, NULL, NULL, 0, yylineno);//to discuss: cant patch label because there is nowhere 
                                                                                            //to save the index - maybe change grammar rules
                                                  
                                                    }
                    | KEYWORD_RETURN SEMICOLON {
                                                if(scope == 0) yyerror("Use of 'return' while not in a fucntion\n");
                                                emit(ret, NULL, NULL, NULL, 0, yylineno);
                                                emit(jump, NULL, NULL, NULL, 0, yylineno);//to discuss: cant patch label because there is nowhere 
                                                                                        //to save the index - maybe change grammar rules

                                                }

%%
int yyerror (char* yaccProvidedMessage) {
    fprintf(stderr, "%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr,"INPUT NOT VALID\n");
    return 1;
}

void backpatchor(int list, int label){
    patchlabel(0,6);
}
//**************************************************************
void backpatchand(int list, int label){
    patchlabel(0,2);
}

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
