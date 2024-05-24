#include "quads.h"

typedef enum avm_memecell_t{
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
}avm_memecell_t;

struct avm_table;

typedef struct avm_memcell{
    avm_memecell_t type;
    union{
        double numVal;
        char* strVal;
        unsigned char boolVal;
        struct avm_table* tableVal;
        unsigned int funcVal;
        char* libfuncVal;
    }data;
}avm_memcell;

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))

avm_memcell stack[AVM_STACKSIZE];
static void avm_initstack(void){
    for(unsigned i=0;i<AVM_STACKSIZE;++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type=nil_m;
    }
}

avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_memcell* key);
void avm_tablesetelem(avm_memcell* key,avm_memcell* value); 

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
}avm_table_bucket;

typedef struct avm_table{
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* boolIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* tableIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* userfuncIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* libfuncIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* nilIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* undefIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
} avm_table;

void avm_tableincrefcounter(avm_table* t);  
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);

avm_table* avm_tablenew(void);
void avm_memcellclear(avm_memcell* m);
void avm_tablebucketdestroy(avm_table_bucket** p);
void avm_tabledestroy(avm_table* t);

#define AVM_STACKENV_SIZE 4
avm_memcell ax,bx,cx;
avm_memcell retval;
unsigned top,topsp;

double consts_getnumber(unsigned index);
char* consts_getstring(unsigned index);
char* libfuncs_getused(unsigned index);
userfunc* userfuncs_get(unsigned index);

avm_memcell* avm_translate_operand(vmarg* arg,avm_memcell* reg);

typedef void (*execute_func_t)(instruction*);

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

 void execute_assign(instruction*);
 void execute_add(instruction*);
 void execute_sub(instruction*);
 void execute_mul(instruction*);
 void execute_div(instruction*);
 void execute_mod(instruction*);
 void execute_uminus(instruction*);
 void execute_and(instruction*);
 void execute_or(instruction*);
 void execute_not(instruction*);
 void execute_jeq(instruction*);
 void execute_jne(instruction*);
 void execute_jle(instruction*);
 void execute_jge(instruction*);
 void execute_jlt(instruction*);
 void execute_jgt(instruction*);
 void execute_call(instruction*);
 void execute_pusharg(instruction*);
 void execute_enterfunc(instruction*);
 void execute_exitfunc(instruction*);
 void execute_newtable(instruction*);
 void execute_tablegetelem(instruction*);
 void execute_tablesetelem(instruction*);
 void execute_nop(instruction*);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_enterfunc,
    execute_exitfunc,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction* code = (instruction*) 0;

#define AVM_ENDING_PC codeSize

void execute_cycle(void);

typedef void (*memclear_func_t)(avm_memcell*);

//to to elege stis diafaneies alla mporei na min xreiazetai
void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);

memclear_func_t memclearFuncs[] = {
    0, //number
    memclear_string, //string
    0, //bool
    memclear_table, //table
    0, //userfunc
    0, //libfunc
    0, //nil
    0 //undef
};

void avm_memcellclear(avm_memcell* m);

void avm_warning(char* format,...);
void avm_assign(avm_memcell* lv,avm_memcell* rv);
void execute_assign(instruction* instr);
void execute_call(instruction* instr);
    
void avm_error(char* format,...);
void avm_callsaveenvironment(void);
char* avm_tostring(avm_memcell* ); //caller frees
void avm_calllibfunc(char *funcname);
void avm_call_functor(avm_table* t);
void avm_push_table_arg(avm_table* t);

void avm_push_envvalue(unsigned val);
void avm_callsaveenvironment(void);
void avm_dec_top(void);

userfunc* avm_getfuncinfo(unsigned address);
void execute_funcenter(instruction* instr);
unsigned avm_get_envvalue(unsigned i);
void execute_funcexit(instruction* unused);

#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

void avm_calllinfunc(char* id);
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned i);
void libfunc_print(void);
void avm_registerlibfunc(char* id,library_func_t addr);

void avm_push_table_arg(avm_table* t);
void execute_pusharg(instruction* instr);

typedef char* (*tostring_func_t)(avm_memcell*);
char* number_tostring(avm_memcell*);
char* string_tostring(avm_memcell*);
char* bool_tostring(avm_memcell*);
char* table_tostring(avm_memcell*);
char* userfunc_tostring(avm_memcell*);
char* libfunc_tostring(avm_memcell*);
char* nil_tostring(avm_memcell*);
char* undef_tostring(avm_memcell*);

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

char* avm_tostring(avm_memcell* m);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef double (*arithmetic_func_t)(double x,double y);
double add_impl(double x,double y);
double sub_impl(double x,double y);
double mul_impl(double x,double y);
double div_impl(double x,double y);
double mod_impl(double x,double y);

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void execute_arithmetic(instruction* instr);

typedef unsigned char (*tobool_func_t)(avm_memcell*);

unsigned char number_tobool(avm_memcell*);
unsigned char string_tobool(avm_memcell*);
unsigned char bool_tobool(avm_memcell*);
unsigned char table_tobool(avm_memcell*);
unsigned char userfunc_tobool(avm_memcell*);
unsigned char libfunc_tobool(avm_memcell*);
unsigned char nil_tobool(avm_memcell*);
unsigned char undef_tobool(avm_memcell*);

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool(avm_memcell* m);
void libfunc_typeof(void);
void execute_newtable(instruction* instr);

avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* index);
void avm_tablesetelem(avm_table* table,avm_memcell* index,avm_memcell* content);
void execute_tablegetelem(instruction* instr);

void execute_tablesetelem(instruction* instr)
void avm_initialize(void);
void library_totalarguments(void);