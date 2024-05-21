#include "SymTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

#define MAX_SIZE 10000

typedef struct FuncStack
{
    SymbolTableEntry arr[MAX_SIZE];
    int top;
} FuncStack;

void initialize_funcstack(FuncStack *fs);
int isEmpty_funcstack(FuncStack *fs);
int isFull_funcstack(FuncStack *fs);
void push_funcstack(FuncStack *fs, SymbolTableEntry value);
SymbolTableEntry* pop_funcstack(FuncStack *fs);
SymbolTableEntry *top_funcstack(FuncStack *fs);

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
    tablesetelem,
    nop
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
    unsigned int taddress;
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
expr *backpatching(expr *e);
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

/*Phase 4*/
typedef enum
{
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a
} vmarg_t;

typedef enum vm_opcode
{
    assign_v,
    jump_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    callfunc_v,
    pusharg_v,
    enterfunc_v,
    exitfunc_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    nop_v
} vm_opcode;

typedef struct vmarg
{
    vmarg_t type;
    unsigned int val;
} vmarg;


typedef struct instruction{
    vm_opcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned int srcLine;
} instruction;

typedef struct userfunc
{
    unsigned int address;
    unsigned int localSize;
    char *id;
} userfunc;

unsigned int consts_newstring(char *s);
unsigned int consts_newnumber(double n);
unsigned int libfuncs_newused(char *s);
unsigned int userfuncs_newfunc(SymbolTableEntry *sym);

void make_operand(expr *e, vmarg *arg);
void make_numberoperand(vmarg *arg, double val);
void make_booloperand(vmarg *arg, unsigned val);
void make_retvaloperand(vmarg *arg);

typedef struct incomplete_jump
{
    unsigned int instrNo;
    unsigned int iaddress;
    struct incomplete_jump *next;
} incomplete_jump;

void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress);
void patch_incomplete_jumps();

void generate_ADD(quad *);
void generate_SUB(quad *);
void generate_MUL(quad *);
void generate_DIV(quad *);
void generate_MOD(quad *);
void generate_UMINUS(quad *);
void generate_AND(quad *);
void generate_OR(quad *);
void generate_NOT(quad *);
void generate_IF_EQ(quad *);
void generate_IF_NOTEQ(quad *);
void generate_IF_LESSEQ(quad *);
void generate_IF_GREATEREQ(quad *);
void generate_IF_LESS(quad *);
void generate_IF_GREATER(quad *);
void generate_JUMP(quad *);
void generate_CALL(quad *);
void generate_PARAM(quad *);
void generate_RET(quad *);
void generate_GETRETVAL(quad *);
void generate_FUNCSTART(quad *);
void generate_FUNCEND(quad *);
void generate_TABLECREATE(quad *);
void generate_TABLEGETELEM(quad *);
void generate_TABLESETELEM(quad *);
void generate_ASSIGN(quad *);
void generate_NOP();

typedef void (*generator_func_t)(quad *);

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_JUMP,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RET,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_TABLECREATE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_NOP
};

void generate(void);

void emit_instruction(instruction *t);
unsigned int nextinstrlabel();

void generate_op(vm_opcode op, quad *q);

void generate_relational(vm_opcode op, quad *q);

void reset_operand(vmarg *arg);

void backpatch_ret_list(returnList *list, unsigned int label);