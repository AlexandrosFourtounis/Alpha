%{
    #include <stdio.h>
    #define YYDEBUG 1

    //#define YYLEX alpha_yylex
    extern int yydebug;
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
%}

%union{
    int intv;
    char* stringv;
    char charv;
    float floatv;
}

%define parse.error verbose
%start program

%token INTEGER KEYWORD_IF KEYWORD_THEN KEYWORD_ELSE KEYWORD_WHILE 
%token KEYWORD_FOR KEYWORD_FUNCTION KEYWORD_RETURN KEYWORD_BREAK KEYWORD_CONTINUE
%token KEYWORD_AND KEYWORD_NOT KEYWORD_OR KEYWORD_LOCAL KEYWORD_TRUE
%token KEYWORD_FALSE KEYWORD_NIL GREATER LESS EQUALS
%token GREATER_EQUAL LESS_EQUAL NOT_EQUAL INCREMENT DECREMENT 
%token STRING REAL
%token IDENTIFIER LEFTBRACE RIGHTBRACE LEFTBRACKET RIGHTBRACKET 
%token LEFTPARENTHESIS RIGHTPARENTHESIS COMMA SEMICOLON COLON 
%token DOT DOUBLEDOT DOUBLECOLON 

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
                    | KEYWORD_BREAK SEMICOLON
                    | KEYWORD_CONTINUE SEMICOLON
                    | block
                    | funcdef
                    | SEMICOLON

expr:                 expr '+' expr
                    | expr '-' expr
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
                    | INCREMENT lvalue
                    | lvalue INCREMENT
                    | DECREMENT lvalue
                    | lvalue DECREMENT
                    | primary

assignexpr:         lvalue '=' expr

primary:            lvalue
                    | call
                    | objectdef
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS
                    | const

lvalue:             IDENTIFIER
                    | KEYWORD_LOCAL IDENTIFIER
                    | DOUBLECOLON IDENTIFIER
                    | member

member:             lvalue DOT IDENTIFIER
                    | lvalue LEFTBRACKET expr RIGHTBRACKET
                    | call DOT IDENTIFIER
                    | call LEFTBRACKET expr RIGHTBRACKET

call:               call LEFTPARENTHESIS elist RIGHTPARENTHESIS
                    | lvalue callsuffix
                    | LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS

callsuffix:         normcall
                    | methodcall

normcall:           LEFTPARENTHESIS elist RIGHTPARENTHESIS

methodcall:         DOUBLECOLON IDENTIFIER LEFTPARENTHESIS elist RIGHTPARENTHESIS // equivalent to lvalue.id(lvalue, elist)

elist:              exprlist
                    | %empty  
                    ;

exprlist:           exprlist  COMMA expr
                    | expr
                    ;
             

objectdef:          LEFTBRACKET  obj RIGHTBRACKET 
                    ;

obj:                elist
                    | indexed
                    ;
                    
indexed:              indexedelem  COMMA indexedelem  
                    | indexedelem
                    ;

indexedelem:        LEFTBRACE expr COLON expr RIGHTBRACE

block:              LEFTBRACE  blockk  RIGHTBRACE
                    ;

blockk:             blockk stmt
                    | %empty   
                    ;

funcdef:            KEYWORD_FUNCTION  IDENTIFIER  LEFTPARENTHESIS idlist RIGHTPARENTHESIS block
                    | KEYWORD_FUNCTION LEFTPARENTHESIS idlist RIGHTPARENTHESIS block

const:              INTEGER | STRING | KEYWORD_NIL | KEYWORD_TRUE | KEYWORD_FALSE

idlist: %empty               
                    | idlist  COMMA IDENTIFIER
                    | IDENTIFIER
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
    yydebug = 1;
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