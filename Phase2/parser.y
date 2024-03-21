%{
    #include <stdio.h>
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
%}
%define parse.error verbose
%start program

%token ID INTEGER KEYWORD_IF KEYWORD_THEN KEYWORD_ELSE KEYWORD_WHILE 
%token KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_RETURN KEYWORD_BREAK KEYWORD_CONTINUE
%token KEYWORD_AND KEYWORD_NOT KEYWORD_OR KEYWORD_LOCAL KEYWORD_TRUE
%token KEYWORD_FALSE KEYWORD_NIL GREATER LESS EQUALS
%token GREATER_EQUAL LESS_EQUAL NOT_EQUAL INCREMENT DECREMENT 
%token STRING REAL
%token IDENTIFIER LEFTBRACE RIGHTBRACE LEFTBRACKET RIGHTBRACKET 
%token LEFTPARENTHESIS RIGHTPARENTHESIS COMMA SEMICOLON COLON 
%token DOT DOUBLEDOT DOUBLECOLON COMMENT

%right '='
%left ','
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%left '(' ')'

%%
program: assignments expressions
        | /*empty*/
        ;
expression: INTEGER
        | ID
        | expression ',' expression
        | expression '+' expression
        | expression '-' expression
        | expression '*' expression
        | expression '/' expression
        | '(' expression ')'
        | '-' expression %prec UMINUS
        ;
expr:   expression '\n'

expressions: expressions expr
            | expr
            ;

assignment: ID '=' expression '\n'
            ;
assignments: assignments assignment
            | 
            ;
%%
int yyerror (char* yaccProvidedMessage) {
    fprintf(stderr, "%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr,"INPUT NOT VALID\n");
    return 1;
}

//**************************************************************

int main(int argc,char **argv){
    if(argc > 1){
        if(!(yyin = fopen(argv[1],"r"))){
            fprintf(stderr,"Cannot open file\n");
            return 1;
        }
    }else{
        yyin = stdin;
    }
    yyparse();
    return 0;
}