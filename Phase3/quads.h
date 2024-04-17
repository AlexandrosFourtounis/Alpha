#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)


typedef enum scopespace_t {
    programVar,
    functionLocal,
    formalArg
} scopespace_t;

typedef enum symbol_t
{
    var_s,
    programfunc_s,
    libraryfunc_s
} symbol_t;

typedef struct symbol {
    char *name;
    enum symbol_t type;
    unsigned int line;
    unsigned int scope;
    //unsigned int active;
    unsigned int offset;
    enum scopespace_t space;
    //unsigned int funcscope;
    struct symbol *next;
} symbol;



scopespace_t currscopespace(void);
unsigned int currscopeoffset(void);
void inccurrscopeoffset(void);
void enterscopespace(void);
void exitscopespace(void);

typedef enum iopcode
{
    assign,
    add,
    sub,
    mul,
    divv,
    mod,
    uminus,
    and,
    or,
    not,
    if_eq,
    if_noteq,
    if_lesseq,
    if_greatereq,
    if_less,
    if_greater,
    call,
    param,
    ret,
    getretval,
    funcstart,
    funcend,
    tablecreate,
    tablegetelem,
    tablesetelem
}iopcode;

typedef struct expr{

}expr;
typedef struct quad{
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    unsigned label;
    unsigned line;
}quad;

quad *quads = (quad *)0;
unsigned total = 0;
unsigned int currQuad = 0;


void expand(void);
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);