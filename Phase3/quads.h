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
    jump,
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
    char *boolConst;
    struct expr *next;
    int truelist;
    int falselist;
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
void resettemp();
void check_arith(expr *e, const char *context);
char *newtempname();
const char* opcode_to_string(iopcode opcode);
expr *newexpr(expr_t t);
expr* emit_iftableitem(expr* e);
expr *emit_ifboolean(expr *e);
expr* newexpr_conststring(char* s);
expr* member_item(expr* lv, char* name);
expr *lvalue_expr(SymbolTableEntry *sym);
SymbolTableEntry *newtemp();
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


expr *newexpr_bool(char *s);
expr* newexpr_constbool(unsigned char b);
expr *newexpr_nil();
expr *newexpr_constnum(double x);
expr *Manage_operations(expr *arg1, iopcode op, expr *arg2);
expr *Manage_comparisonopers(expr* arg1, char* op, expr* arg2);
expr *make_call(expr *lv, expr *reversed_elist);

typedef struct call
{
    expr* elist;
    int method;
    char *name;
}calls;

typedef struct reversed_list{
    expr *item;
    struct reversed_list *next;
} reversed_list;

typedef struct for_struct{
    unsigned int test;
    unsigned int enter;
} for_struct;

typedef struct stmt_struct{
    int breaklist;
    int contlist;
} stmt_struct;

    reversed_list *
    createExprNode(expr *item);
void addToExprList(reversed_list **head, expr *item);
reversed_list *get_last(reversed_list *head);
int mergelist (int l1, int l2); //added
void patchlist(int list, int label);
stmt_struct* make_stmt ();
int newlist(int i);