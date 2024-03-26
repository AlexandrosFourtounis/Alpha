/* --------------------------- */
/* Phase 1 hy340               */
/* Alexandros Fourtounis 5031  */
/* Dimitris Asimakopoulos 4845 */
/* Tsanta Georgia Marina 5020  */
/* --------------------------- */

%{
    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
//#define YY_DECL int alpha_yylex(void *yylval)

int tokens = 0;
int line_start_comment = 0;

typedef struct {
    char * regex;
    char *value;
    int occurence;
    int line;
    char * type;
    struct alpha_token_t *next;
}alpha_token_t;

alpha_token_t *token_list = NULL;

void insert_token(char *regex, char *value, int line,char *type) {
    alpha_token_t *new_token = malloc(sizeof(alpha_token_t));
    new_token->type = strdup(type);
    new_token->regex = strdup(regex);
    new_token->value = strdup(value);
    tokens++;
    new_token->occurence = tokens;
   
    new_token->line = line;
    new_token->next = NULL;

    if (token_list == NULL) {
        token_list = new_token;
    } else {
        alpha_token_t *current = token_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_token;
    }
}

void print_tokens() {
    alpha_token_t *current = token_list;
    printf("-------------------		Lexical Analysis		-------------------\n\n");
    for (; current != NULL; current = current->next) {
        printf("%d:      #%d     \"%s\"    %s       %s      <-- %s\n", current->line, current->occurence, current->value, current->regex, current->value, current->type);
    }
}

void print_tokens_to_file(char *filename) {
    FILE *fp;
    if (!(fp = fopen(filename, "w+"))) {
        fprintf(stderr, "Cannot open file %s for writing\n", filename);
        return;
    }
    fprintf(fp, "\n-------------------    Lexical Analysis    -------------------\n\n");

    alpha_token_t *current = token_list;
    for (; current != NULL; current = current->next) {
        printf("%d:      #%d     \"%s\"    %s       %s      <-- %s\n", current->line, current->occurence, current->value, current->regex, current->value, current->type);
    }
    fclose(fp);
    printf("Output saved to file \"%s\"\n", filename);
}

%}

%option noyywrap
%option yylineno

IF "if"
THEN "then"
ELSE "else"
WHILE "while"
FOR "for"
FUNCTION "function"
RETURN "return"
BREAK "break"
CONTINUE "continue"
AND "and"
NOT "not"
OR "or"
LOCAL "local"
TRUE "true"
FALSE "false"
NIL "nil"

MINUS "-"
PLUS "+"
TIMES "*"
DIVIDE "/"
MODULO "%"
ASSIGNMENT "="
GREATER ">"
LESS "<"
EQUALS "=="
NOT_EQUAL "!="
GREATER_EQUAL ">="
LESS_EQUAL "<="
INCREMENT "++"
DECREMENT "--"

INTEGER (0[xX][0-9A-Fa-f]+)|([0-9]+)
REAL [0-9]*\.[0-9](e|E)?[0-9]*
STRING 	\"([^"\\]|\\.)*\" 

IDENTIFIER [a-zA-Z][a-zA-Z_0-9]*

LEFTBRACE "\{"
RIGHTBRACE "\}"

LEFTBRACKET "\["
RIGHTBRACKET "\]"

LEFTPARENTHESIS "\("
RIGHTPARENTHESIS "\)"


COMMA "\,"
SEMICOLON "\;"
COLON "\:"
DOUBLECOLON "::"
DOT "\."
DOUBLEDOT "\.\."

ERROR .


%x COMMENT MULTI_COMMENT NESTED_COMMENT 
%x STR

%%
"//" { BEGIN(COMMENT); }
<COMMENT>\n { BEGIN(INITIAL); }
<COMMENT>.* {  }


\"      { BEGIN(STR); }
<STR>.  {
    if (yytext[0] == '\\') {
    }  else {
    }
}
<STR><<EOF>> {
    printf("\x1b[31m" "\x1b[1m"  "WARNING: \n" "\x1b[0m");
    printf("\x1b[1m"  "String not closed at line: %d\n" "\x1b[0m", yylineno);
    exit(1);
}

"/*"   { BEGIN(MULTI_COMMENT); line_start_comment = yylineno; }
<MULTI_COMMENT>[^*]*        { }
<MULTI_COMMENT>"*"+[^*/]*   { }
<MULTI_COMMENT>"/"+"*"         {  printf("sfwf"); BEGIN(NESTED_COMMENT);  }
<MULTI_COMMENT>"*/"         { 
    char print_lines[20];
    sprintf(print_lines, "%d-%d", line_start_comment, yylineno);
    insert_token("MULTI-LINE COMMENT", print_lines, yylineno, "enumerated"); BEGIN(INITIAL); }

<NESTED_COMMENT>[^*]*        { }
<NESTED_COMMENT>"*"+[^*/]*   { }
<NESTED_COMMENT>"*/"         { 
    char print_lines[20];
    sprintf(print_lines, "%d-%d", line_start_comment, yylineno);
    insert_token("MULTI-LINE NESTED COMMENT", print_lines, yylineno, "enumerated"); BEGIN(MULTI_COMMENT); }

<NESTED_COMMENT>"/*"         { 
    fprintf(stderr, "Error: Nested multi-line comment found at line %d\n", yylineno);
    BEGIN(INITIAL);
}

[ \t\n] 
<INITIAL><<EOF>> {return 0;}

{IF} {
    insert_token("KEYWORD", "if", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_IF;
}
{THEN} {
    insert_token("KEYWORD", "then", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_THEN;
}
{ELSE} {
    insert_token("KEYWORD", "else", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_ELSE;
}
{WHILE} {
    insert_token("KEYWORD", "while", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_WHILE;
}
{FOR} {
    insert_token("KEYWORD", "for", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_FOR;
}
{FUNCTION} {
    insert_token("KEYWORD", "function", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_FUNCTION;
}
{RETURN} {
    insert_token("KEYWORD", "return", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_RETURN;
}
{BREAK} {
    insert_token("KEYWORD", "break", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_BREAK;
}
{CONTINUE} {
    insert_token("KEYWORD", "continue", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_CONTINUE;
}
{AND} {
    insert_token("KEYWORD", "and", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_AND;
}
{NOT} {
    insert_token("KEYWORD", "not", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_NOT;
}
{OR} {
    insert_token("KEYWORD", "or", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_OR;
}
{LOCAL} {
    insert_token("KEYWORD", "local", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_LOCAL;
}
{TRUE} {
    insert_token("KEYWORD", "true", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_TRUE;
}
{FALSE} {
    insert_token("KEYWORD", "false", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_FALSE;
}
{NIL} {
    insert_token("KEYWORD", "nil", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return KEYWORD_NIL;
}

{ASSIGNMENT} {
    insert_token("OPERATOR ASSIGNMENT", "=", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '=';
}
{PLUS} {
    insert_token("OPERATOR PLUS", "+", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '+';
}
{MINUS} {
    insert_token("OPERATOR MINUS", "-", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '-';
}
{TIMES} {
    insert_token("OPERATOR TIMES", "*", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '*';
}
{DIVIDE} {
    insert_token("OPERATOR DIVIDE", "/", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '/';
}
{MODULO} {
    insert_token("OPERATOR MODULO", "%", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return '%';
}
{GREATER} {
    insert_token("OPERATOR GREATER", ">", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return GREATER;
}
{LESS} {
    insert_token("OPERATOR LESS", "<", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return LESS;
}
{EQUALS} {
    insert_token("OPERATOR EQUALS", "==", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return EQUALS;
}
{NOT_EQUAL} {
    insert_token("OPERATOR NOT EQUAL", "!=", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return NOT_EQUAL;
}
{GREATER_EQUAL} {
    insert_token("OPERATOR GREATER EQUAL", ">=", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return GREATER_EQUAL;
}
{LESS_EQUAL} {
    insert_token("OPERATOR LESS EQUAL", "<=", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return LESS_EQUAL;
}
{INCREMENT} {
    insert_token("OPERATOR PLUS_PLUS", "++", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return INCREMENT;
}
{DECREMENT} {
    insert_token("OPERATOR MINUS_MINUS", "--", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return DECREMENT;
}

{INTEGER} {
    insert_token("INTCONST", yytext, yylineno,"int");
    yylval.intv = atoi(yytext);
    return INTEGER;
}
{REAL} {
    insert_token("REALCONST", yytext, yylineno,"real");
    yylval.floatv = atof(yytext);
    return REAL;
}
{STRING} {
   char * str = strdup(yytext);
    int i = 0;
    int j = 0;

    while(str[i]){
        switch(str[i]) {
            case '\\':
                switch(str[i+1]) {
                    case 'n':
                        str[j] = '\n';
                        i += 2;
                        break;
                    case 't':
                        str[j] = '\t'; 
                        i += 2;
                        break;
                    case 'r':
                        str[j] = '\r';
                        i += 2;
                        break;
                    case 'v':
                        str[j] = '\v';
                        i += 2;
                        break;
                    case '\\':
                        if (str[i+2] == '\"') {
                            str[j] = '\\';
                            str[j+1] = '\"';
                            i += 3;
                        } else {
                            str[j] = '\\';
                            i += 2;
                        }
                        break;
                    case '\"':
                        str[j] = '\"';
                        i += 2;
                        break;
                    default:
                        str[j] = str[i];
                        i++;
                        printf("\x1b[31m" "\x1b[1m"  "WARNING: \n" "\x1b[0m");
                        printf("\x1b[1m"  "Invalid escape sequence : \\%c  at line: %d\n" "\x1b[0m",str[i],yylineno);
                }
                break;
            default:
                str[j] = str[i];
                i++;
        }
        j++;
    }

    if(str[j-1] != '"'){
        printf("\x1b[31m" "\x1b[1m"  "WARNING: \n" "\x1b[0m");
        printf("\x1b[1m"  "String not closed at line: %d\n" "\x1b[0m",yylineno);
        exit(1) ;
    }
    str[j] = '\0';

    insert_token("STRING", str, yylineno,"char*");
    yylval.stringv = str;
    return STRING;
    free(str);
}


{IDENTIFIER} {
    insert_token("IDENT", yytext, yylineno,"char*");
    yylval.stringv = strdup(yytext);
    return IDENTIFIER;
}
{LEFTBRACE} {
    insert_token("PUNCTUATION LEFT_BRACE", "{", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return LEFTBRACE;
}
{RIGHTBRACE} {
    insert_token("PUNCTUATION RIGHT_BRACE", "}", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return RIGHTBRACE;
}
{LEFTBRACKET} {
    insert_token("PUNCTUATION LEFT_BRACKET", "[", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return LEFTBRACKET;
}
{RIGHTBRACKET} {
    insert_token("PUNCTUATION RIGHT_BRACKET", "]", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return RIGHTBRACKET;
}
{LEFTPARENTHESIS} {
    insert_token("PUNCTUATION LEFT_PARENTHESIS", "(", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return LEFTPARENTHESIS;
}
{RIGHTPARENTHESIS} {
    insert_token("PUNCTUATION RIGHT_PARENTHESIS", ")", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return RIGHTPARENTHESIS;
}
{COMMA} {
    insert_token("PUNCTUATION COMMA", ",", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return COMMA;
}
{SEMICOLON} {
    insert_token("PUNCTUATION SEMICOLON", ";", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return SEMICOLON;
}
{COLON} {
    insert_token("PUNCTUATION COLON", ":", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return COLON;
}
{DOUBLECOLON} {
    insert_token("PUNCTUATION DOUBLE_COLON", "::", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return DOUBLECOLON;
}
{DOT} {
    insert_token("PUNCTUATION DOT", ".", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return DOT;
}
{DOUBLEDOT} {
    insert_token("PUNCTUATION DOUBLE_DOT", "..", yylineno,"enumerated");
    yylval.stringv = strdup(yytext);
    return DOUBLEDOT;
}

{ERROR} {
    printf("\x1b[31m" "\x1b[1m"  "WARNING: \n" "\x1b[0m");
    printf("\x1b[1m"  "Undefined char at line: %d is : %s\n" "\x1b[0m",yylineno,yytext);
}

%%