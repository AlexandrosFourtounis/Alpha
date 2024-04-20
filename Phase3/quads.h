#include "SymTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

typedef enum expr_t
{
    var_e,
    tableitem_e,
    programfunc_e,
    libraryfunc_e,
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    constnum_e,
    constbool_e,
    conststring_e,
    nil_e
}expr_t;

/*
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
    
    //unsigned int funcscope;
    struct symbol *next;
} symbol;
*/




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
    expr_t type;
    SymbolTableEntry *sym;
    struct expr *index;
    double numConst;
    char *strConst;
    unsigned char boolConst;
    struct expr *next;
}expr;


typedef struct quad{
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    unsigned int label;
    unsigned int line;
}quad;

extern quad *quads;
extern unsigned int total;
extern unsigned int currQuad;


void expand(void);
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned int label, unsigned int line);

//UTILS
void check_arith(expr *e, const char *context);
expr *lvalue_expr(SymbolTableEntry *sym);
expr *newexpr(expr_t t);
char *newtempname();
void resettemp();
SymbolTableEntry *newtemp();
expr* emit_iftableitem(expr* e);
expr* newexpr_conststring(char* s);
expr* member_item(expr* lv, char* name);

scopespace_t currscopespace(void);
unsigned int currscopeoffset(void);
void inccurrscopeoffset(void);
void enterscopespace(void);
void exitscopespace(void);
void resetformalargsoffset();
void resetfunctionlocalsoffset();
void restorecurrscopeoffset(unsigned int n);
unsigned int nextquadlabel();
void patchlabel(unsigned int quadNo, unsigned int label);
void print_quads();
expr* Manage_operations(expr *arg1, iopcode op, expr *arg2);

