%{
    
#include <stdlib.h>
#include <util.h>
#include <stdio.h>
#include <string.h>
#define YY_DECL int alpha_yylex(void *yylval)

#define CURRENT_LINE (YY_CURRENT_BUFFER->yylineno)

typedef struct {
    char * regex;
    char *value;
    int occurence;
    int line;
    char * type;
}alpha_token_t;

alpha_token_t *token_list = NULL;

void insert_token(char *type, char *value, int line) {
    alpha_token_t *new_token = malloc(sizeof(alpha_token_t));
    new_token->type = strdup(type);
    new_token->value = strdup(value);
    +new_token->occurence;
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

%}

%option noyywrap
%option yylineno

KEYWORD IF+THEN+ELSE+WHILE+FOR+FUNCTION+RETURN+BREAK+CONTINUE+AND+NOT+OR+LOCAL+TRUE+FALSE+NIL
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
STRING \"[^\n"]*\"
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]*

LEFTBRACE "\{"
RIGHTBRACE "\}"

LEFTBRACKET "\["
RIGHTBRACKET "\]"

LEFTPARENTHESIS "\("
RIGHTPARENTHESIS "\)"
ESCAPE   [ \t\n\r\v]

COMMA "\,"
SEMICOLON "\;"
COLON "\:"
DOUBLECOLON "::"
DOT "\."
DOUBLEDOT "\.\."
COMMENT "\/\/".*

%x MULTI_COMMENT INCLUDE

%%
{IF} {
    insert_token("KEYWORD", "if", CURRENT_LINE,"enumerated");
}
{THEN} {
    insert_token("KEYWORD", "then", CURRENT_LINE,"enumerated");
}
{ELSE} {
    insert_token("KEYWORD", "else", CURRENT_LINE,"enumerated");
}
{WHILE} {
    insert_token("KEYWORD", "while", CURRENT_LINE,"enumerated");
}
{FOR} {
    insert_token("KEYWORD", "for", CURRENT_LINE,"enumerated");
}
{FUNCTION} {
    insert_token("KEYWORD", "function", CURRENT_LINE,"enumerated");
}
{RETURN} {
    insert_token("KEYWORD", "return", CURRENT_LINE,"enumerated");
}
{BREAK} {
    insert_token("KEYWORD", "break", CURRENT_LINE,"enumerated");
}
{CONTINUE} {
    insert_token("KEYWORD", "continue", CURRENT_LINE,"enumerated");
}
{AND} {
    insert_token("KEYWORD", "and", CURRENT_LINE,"enumerated");
}
{NOT} {
    insert_token("KEYWORD", "not", CURRENT_LINE,"enumerated");
}
{OR} {
    insert_token("KEYWORD", "or", CURRENT_LINE,"enumerated");
}
{LOCAL} {
    insert_token("KEYWORD", "local", CURRENT_LINE,"enumerated");
}
{TRUE} {
    insert_token("KEYWORD", "true", CURRENT_LINE,"enumerated");
}
{FALSE} {
    insert_token("KEYWORD", "false", CURRENT_LINE,"enumerated");
}
{NIL} {
    insert_token("KEYWORD", "nil", CURRENT_LINE,"enumerated");
}

{ASSIGNMENT} {
    insert_token("OPERATOR ASSIGNMENT", "=", CURRENT_LINE,"enumerated");
}
{PLUS} {
    insert_token("OPERATOR PLUS", "+", CURRENT_LINE,"enumerated");
}
{MINUS} {
    insert_token("OPERATOR MINUS", "-", CURRENT_LINE,"enumerated");
}
{TIMES} {
    insert_token("OPERATOR TIMES", "*", CURRENT_LINE,"enumerated");
}
{DIVIDE} {
    insert_token("OPERATOR DIVIDE", "/", CURRENT_LINE,"enumerated");
}
{MODULO} {
    insert_token("OPERATOR MODULO", "%", CURRENT_LINE,"enumerated");
}
{GREATER} {
    insert_token("OPERATOR GREATER", ">", CURRENT_LINE,"enumerated");
}
{LESS} {
    insert_token("OPERATOR LESS", "<", CURRENT_LINE,"enumerated");
}
{EQUALS} {
    insert_token("OPERATOR EQUALS", "==", CURRENT_LINE,"enumerated");
}
{NOT_EQUAL} {
    insert_token("OPERATOR NOT EQUAL", "!=", CURRENT_LINE,"enumerated");
}
{GREATER_EQUAL} {
    insert_token("OPERATOR GREATER EQUAL", ">=", CURRENT_LINE,"enumerated");
}
{LESS_EQUAL} {
    insert_token("OPERATOR LESS EQUAL", "<=", CURRENT_LINE,"enumerated");
}
{INCREMENT} {
    insert_token("OPERATOR PLUS_PLUS", "++", CURRENT_LINE,"enumerated");
}
{DECREMENT} {
    insert_token("OPERATOR MINUS_MINUS", "--", CURRENT_LINE,"enumerated");
}

{INTEGER} {
    insert_token("INTCONST", yytext, CURRENT_LINE,"int");
}
{REAL} {
    insert_token("REALCONST", yytext, CURRENT_LINE,"float");
}
{STRING} {
    insert_token("STRING", yytext, CURRENT_LINE,"char*");
}
{IDENTIFIER} {
    insert_token("IDENT", yytext, CURRENT_LINE,"char*");
}
{LEFTBRACE} {
    insert_token("PUNCTUATION LEFT_BRACE", "{", CURRENT_LINE,"enumerated");
}
{RIGHTBRACE} {
    insert_token("PUNCTUATION RIGHT_BRACE", "}", CURRENT_LINE,"enumerated");
}
{LEFTBRACKET} {
    insert_token("PUNCTUATION LEFT_BRACKET", "[", CURRENT_LINE,"enumerated");
}
{RIGHTBRACKET} {
    insert_token("PUNCTUATION RIGHT_BRACKET", "]", CURRENT_LINE,"enumerated");
}
{LEFTPARENTHESIS} {
    insert_token("PUNCTUATION LEFT_PARENTHESIS", "(", CURRENT_LINE,"enumerated");
}
{RIGHTPARENTHESIS} {
    insert_token("PUNCTUATION RIGHT_PARENTHESIS", ")", CURRENT_LINE,"enumerated");
}
{COMMA} {
    insert_token("PUNCTUATION COMMA", ",", CURRENT_LINE,"enumerated");
}
{SEMICOLON} {
    insert_token("PUNCTUATION SEMICOLON", ";", CURRENT_LINE,"enumerated");
}
{COLON} {
    insert_token("PUNCTUATION COLON", ":", CURRENT_LINE,"enumerated");
}
{DOUBLECOLON} {
    insert_token("PUNCTUATION DOUBLE_COLON", "::", CURRENT_LINE,"enumerated");
}
{DOT} {
    insert_token("PUNCTUATION DOT", ".", CURRENT_LINE,"enumerated");
}
{DOUBLEDOT} {
    insert_token("PUNCTUATION DOUBLE_DOT", "..", CURRENT_LINE,"enumerated");
}
{COMMENT} {
    insert_token("COMMENT LINE_COMMENT", "", CURRENT_LINE,"char*");
}
{ESCAPE} {
}


%%

"/*"    BEGIN(MULTI_COMMENT);
<MULTI_COMMENT>[^*/]*
<MULTI_COMMENT>"*"+[^*/]*
<MULTI_COMMENT>"*"+"/" BEGIN(INITIAL);

int main() {
    // Set up any necessary initialization code here

    // Call the lexer to start tokenizing input
    yylex();

    // Clean up any resources or perform final actions here

    return 0;
}
