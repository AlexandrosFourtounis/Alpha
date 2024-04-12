enum iopcode
{
    assign,
    add,
    sub,
    mul,
    div,
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
};

struct expr;
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

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

void expand(void);
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);