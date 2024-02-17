%{
    


%}

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

OPERATOR "[-+*/%=<>]"
OPERATOR "=="
OPERATOR "!="
OPERATOR ">="
OPERATOR "<="
OPERATOR "++"
OPERATOR "--"

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
