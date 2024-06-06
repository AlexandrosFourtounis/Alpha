#include "avm.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_MULTIPLIER 65599

unsigned int totalActuals = 0;
libfuncp *libfuncslist = NULL;
int totallibfuncs;
char **libfuncst;
int totalstringconsts;
char **stringslist ;
int totalglobalv;
int totalnumconst;
double *numberconstslist;
int totaluserfuncs;
userfunc *userFuncs;

char *typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};

void avm_tableincrefcounter(avm_table *t)
{
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter)
        avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket **p)
{
    unsigned i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i)
        p[i] = (avm_table_bucket *)0;
}

avm_table *avm_tablenew(void)
{
    avm_table *t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->boolIndexed);
    avm_tablebucketsinit(t->tableIndexed);
    avm_tablebucketsinit(t->userfuncIndexed);
    avm_tablebucketsinit(t->libfuncIndexed);
    avm_tablebucketsinit(t->nilIndexed);
    avm_tablebucketsinit(t->undefIndexed);
    return t;
}

/*copilot did it
void avm_memcellclear(avm_memcell* m){
    if(m->type!=undef_m){
        m->type=undef_m;
        memset(&(m->data),0,sizeof(m->data));
    }
} to sosto dinetai sthn dialexh 15 kai to exoume valei grammh 139
*/

void avm_tablebucketdestroy(avm_table_bucket **p)
{
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p)
    {
        for (avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}

void avm_tabledestroy(avm_table *t)
{
    avm_tablebucketdestroy(t->strIndexed);
    avm_tablebucketdestroy(t->numIndexed);
    avm_tablebucketdestroy(t->boolIndexed);
    avm_tablebucketdestroy(t->tableIndexed);
    avm_tablebucketdestroy(t->userfuncIndexed);
    avm_tablebucketdestroy(t->libfuncIndexed);
    avm_tablebucketdestroy(t->nilIndexed);
    avm_tablebucketdestroy(t->undefIndexed);
    free(t);
}

char *userfunc_tostring(avm_memcell *mem)
{
    //not needed i think
    return userFuncs[mem->data.funcVal].id;
}

char *libfuncs_getused(unsigned index)
{
    return libfuncst[index];
}

userfunc *userfuncs_get(unsigned index)
{
    // not needed kratame to proto
}

void execute_enterfunc(instruction *instr)
{
    userfunc *funcInfo = userfuncs_get(instr->result.val);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_exitfunc(instruction *i) 
{
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    while (++oldTop <= top)
    {
        avm_memcellclear(&stack[oldTop]);
    }
}

void avm_warning(char *warning, instruction *q)
{
     fprintf(stderr, "\033[1;33mWARNING: \033[0;33m%s in line: %u\n\033[0m", warning, code->srcLine);
}


void avm_error(char *format, instruction *q)
{
    fprintf(stderr, "\033[1;31mERROR: \033[0;31m");
    fprintf(stderr, format, code->srcLine);
    fprintf(stderr, "\033[0m\n");
    executionFinished = 1;
}

library_func_t avm_getlibraryfunc(char* id){
    libfuncp *curr = libfuncslist;
    while(curr){
        if(strcmp(curr->id, id) == 0){
            return curr->address;
        }
        curr = curr->next;
    }
    return NULL;
}

void avm_calllibfunc(char *funcname)
{
    library_func_t f = avm_getlibraryfunc(funcname);
    if (!f)
    {
        avm_error("unsupported lib func '%s' called!", &code[pc]);
    }
    else
    {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if (!executionFinished)
        {
            execute_funcexit((instruction *)0);
        }
    }
}

void avm_calltablefunc(char *funcname)
{
    // einai gia functors ara pros to paron den ginetai 
}
char *string_tostring(avm_memcell *mem) {
    return mem->data.strVal;
}

char *number_tostring(avm_memcell *mem) {
    char* buff;
    buff = malloc(sizeof(char*));
    sprintf(buff, "%.3f", mem->data.numVal);
    return buff;
}

char *bool_tostring(avm_memcell *mem) {
    return mem->data.boolVal?"TRUE":"FALSE";
}

char *table_tostring(avm_memcell *mem) {
    char* buff;
    char* buffbuff;
    buff = malloc(8 * sizeof(char*));
    buffbuff = malloc(sizeof(char*));
    strcat(buff, "[ ");
    int i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        avm_table_bucket* temp = mem->data.tableVal->strIndexed[i];
        while (temp != NULL) {
            strcat(buff, "{\"");
            strcat(buff, temp->key.data.strVal);
            strcat(buff, "\":");
            strcat(buff, avm_tostring(&(temp->value)));
            strcat(buff, "} ");
            temp = temp->next;
        }

        temp = mem->data.tableVal->numIndexed[i];
        while (temp != NULL) {
            strcat(buff, "{");
            sprintf(buffbuff, "%d", (int)temp->key.data.numVal);
            strcat(buff, buffbuff);
            strcat(buff, ":");
            strcat(buff, avm_tostring(&(temp->value)));
            strcat(buff, "} ");

            temp = temp->next;
        }
    }

    strcat(buff, "]");

    return buff;
}

char *libfunc_tostring(avm_memcell *mem) {
    char* buff = malloc(sizeof(char*));
    sprintf(buff, "Library Function : %s", mem->data.libfuncVal);
    return buff;
}

char *nil_tostring(avm_memcell *mem) {
    return "NIL";
}

char *undef_tostring(avm_memcell *mem) {
    return "UNDEFINED";
}

// void execute_mod(instruction *){}
// void execute_uminus(instruction *) {}
void execute_and(instruction *in) {  assert(0); return; }
void execute_or(instruction *in) { assert(0); return;}
void execute_not(instruction *in) {assert(0); return;}
void execute_jne(instruction *i) {
    printf("execute_jne\n");
    assert(i->result.type == label_a);

    avm_memcell* mem1 = avm_translate_operand(&i->arg1, &ax);
    avm_memcell* mem2 = avm_translate_operand(&i->arg2, &bx);

    unsigned char result = 0;

    if (mem1->type == undef_m || mem2->type == undef_m) {
        avm_error("undefined operand comparison", &code[pc]);
    } else if (mem1->type == nil_m || mem2->type == nil_m) {
        result = mem1->type == nil_m && mem2->type == nil_m;
    } else if (mem1->type == bool_m || mem2->type == bool_m) {
        result = (avm_tobool(mem1) != avm_tobool(mem2));
    } else if (mem1->type != mem2->type) {
        avm_error("Comparison between ", &code[pc]);
        printf("%s and %s is illegal because they're different", typeStrings[mem1->type], typeStrings[mem2->type]);
    } else {
        result = avm_tobool(mem1) != avm_tobool(mem2);
    }

    if (!executionFinished && !result) {
        pc = i->result.val;
    }
}
typedef unsigned char (*comp_func)(double x, double y);
unsigned char less_eq(double x, double y) { return x <= y; }
unsigned char greater_eq(double x, double y) { return x >= y; }
unsigned char less(double x, double y) { return x < y; }
unsigned char greater(double x, double y) { return x > y; }
comp_func comparisonFuncs[] = {less_eq, greater_eq, less, greater};

void execute_jle(instruction *i) {
    assert(i->result.type == label_a);

    avm_memcell* mem1 = avm_translate_operand(&i->arg1, &ax);
    avm_memcell* mem2 = avm_translate_operand(&i->arg2, &bx);
    assert(mem1 && mem2);

    unsigned char result = 0;

    if (mem1->type == undef_m || mem2->type == undef_m) {
        avm_error("undefined operand comparison", &code[pc]);
    } else if (mem1->type == nil_m || mem2->type == nil_m) {
        result = mem1->type == nil_m && mem2->type == nil_m;
    } else if (mem1->type == bool_m || mem2->type == bool_m) {
        result = (avm_tobool(mem1) == avm_tobool(mem2));
    } else if (mem1->type != mem2->type) {
        avm_error("Comparison between ", &code[pc]);
        printf("%s and %s is illegal because they're different", typeStrings[mem1->type], typeStrings[mem2->type]);
    } else {
        comp_func op = comparisonFuncs[i->opcode - jle_v];
        result = (*op)(mem1->data.numVal, mem2->data.numVal);
    }

    if (!executionFinished && result) {
        pc = i->result.val;
    }
}

void execute_jge(instruction *i) {
    execute_jle(i);
}

void execute_jlt(instruction *i) {
    execute_jle(i);
}

void execute_jgt(instruction *i) {
    execute_jle(i);
}


void execute_nop(instruction *i) {}
double consts_getnumber(unsigned index){
    return numberconstslist[index];
} //needs file parsing to find numbers 
char *consts_getstring(unsigned index){
     return stringslist[index];
} //needs file parsing to find strings


avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    switch (arg->type)
    {
    case global_a:
        return &stack[AVM_STACKSIZE - 1 - arg->val];
    case local_a:
        return &stack[topsp - arg->val];
    case formal_a:
        return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
    case retval_a:
        return &retval;
    case number_a:
    {
        reg->type = number_m;
        reg->data.numVal = consts_getnumber(arg->val);
        return reg;
    }
    case string_a:
    {
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstring(arg->val));
        return reg;
    }
    case bool_a:
    {
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;
    }
    case nil_a:
        reg->type = nil_m;
        return reg;
    case userfunc_a:
    {
        reg->type = userfunc_m;
        reg->data.funcVal = arg->val; // h ayto h apo kato
        //reg->data.funcVal = userfuncs_get(arg->val)->address;
        return reg;
    }
    case libfunc_a:
    {
        reg->type = libfunc_m;
        reg->data.libfuncVal = libfuncs_getused(arg->val);
        return reg;
    }
    default:
        assert(0);
    }
}

void execute_cycle(void)
{
    printf("in execute_cycle");
    printf("Debug: pc = %d, AVM_ENDING_PC = %d\n", pc, AVM_ENDING_PC); //debug
    if (executionFinished)
    {
        return;
    }
    else if (pc == AVM_ENDING_PC)
    {
        executionFinished = 1;
        return;
    }
    else
    {
        //debug
        if (!(pc < AVM_ENDING_PC)) {
            printf("Debug: pc = %d, AVM_ENDING_PC = %d\n", pc, AVM_ENDING_PC);
        }
        assert(pc < AVM_ENDING_PC);
        instruction *instr = &code[pc];
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if (instr->srcLine)
        {
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        executeFuncs[instr->opcode](instr);
        if (pc == oldPC)
        {
            ++pc;
        }
    }
    printf("done withe execution_CYCLE\n");
}

extern void memclear_string(avm_memcell *m)
{
    assert(m->data.strVal);
    free(m->data.strVal);
}

extern void memclear_table(avm_memcell *m)
{
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell *m)
{
    if (m->type != undef_m)
    {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
        {
            (*f)(m);
        }
        m->type = undef_m;
    }
}

// sth diafaneia gia edo stack[AVM_STACKSIZE-1] leei stack[N-1]. to copilot eipe to 1o
void execute_assign(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv); // should do similar assertion tests here
    avm_assign(lv, rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
    if (lv == rv)
    {
        return;
    }
    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    {
        return;
    }
    if (rv->type == undef_m)
    {
        avm_warning("assigning from 'undef' content!", &code[pc]);
    }
    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));
    if (lv->type == string_m)
    {
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if (lv->type == table_m)
    {
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_call(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    switch (func->type)
    {
    case userfunc_m:
    {
        avm_callsaveenvironment();
        pc = func->data.funcVal;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == enterfunc_v);
        break;
    }
    case string_m:
        avm_calllibfunc(func);
        break;
    case libfunc_m:
        avm_calllibfunc(func);
        break;
    case table_m:
        avm_calltablefunc(func);
        break;
    default:
    {
        char *s = avm_tostring(func);
        avm_error("call: cannot bind '%s' to function!", s);
        free(s);
        executionFinished = 1;
    }
    }
}

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey)
{
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash;
}

unsigned int hasfornum(double x)
{
    unsigned long z = abs((int)x);
    return z % 211;
}

avm_memcell *avm_tablegetelem(avm_table *table, avm_memcell *index){
    unsigned int ix = 0;
    avm_table_bucket *curr, *prev = NULL, *pair;
    assert(table && index);

    switch (index->type)
    {
    case string_m:
        ix = SymTable_hash(index->data.strVal);
        curr = table->strIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp((curr->key).data.strVal, index->data.strVal))
            {
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case number_m:
        ix = hasfornum(index->data.numVal);
        curr = table->numIndexed[ix];
        while (curr)
        {
            prev = curr;
            if ((curr->key).data.numVal == index->data.numVal)
            {
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case bool_m:
        ix = index->data.boolVal;
        curr = table->boolIndexed[ix];
        if (curr != NULL)
        {
            //avm_tableincrefcounter(curr->value.data.tableVal);
            return &(curr->value);
        }
        break;
    case userfunc_m:
        ix = SymTable_hash(userFuncs[index->data.funcVal].id);
        curr = table->userfuncIndexed[ix];
        while (curr)
        {
            prev = curr;
            if (!strcmp(userFuncs[index->data.funcVal].id, userFuncs[curr->key.data.funcVal].id) && userFuncs[index->data.funcVal].address == userFuncs[curr->key.data.funcVal].address) //address needless?
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case libfunc_m:
        ix = SymTable_hash(index->data.libfuncVal);
        curr = table->libfuncIndexed;
        while (curr)
        {
            prev = curr;
            if (!strcmp(index->data.libfuncVal, (curr->key).data.libfuncVal))
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    case table_m:
        ix = index->data.tableVal->refCounter % 211;
        curr = table->tableIndexed[ix];
        while (curr)
        {
            prev = curr;

            if (index->data.tableVal == (curr->key).data.tableVal)
            {
                /*if (curr->value.type == table_m)
                {
                    avm_tableincrefcounter(curr->value.data.tableVal);
                }*/
                return &(curr->value);
            }
            curr = curr->next;
        }
        break;
    }

    return NULL;
}

void avm_call_functor(avm_table *t)
{
    cx.type = table_m;
    cx.data.strVal = "()";
    avm_memcell *f = avm_tablegetelem(t, &cx);
    if (!f)
    {
        avm_error("In calling table: no '()' element found!", &code[pc]);
    }
    else if (f->type == table_m)
    {
        avm_call_functor(f->data.tableVal);
    }
    else if (f->type == userfunc_a)
    {
        avm_push_table_arg(t);
        avm_callsaveenvironment();
        pc = f->data.funcVal;
        assert(pc < AVM_ENDING_PC && code[pc].opcode == enterfunc_v);
    }
    else
    {
        avm_error("In calling table: illegal '()' element value!", &code[pc]);
    }
}

void avm_dec_top(void)
{
    if (!top)
    {
        avm_error("stack overflow", &code[pc]);
        executionFinished = 1;
    }
    else
    {
        --top;
    }
}

void avm_push_envvalue(unsigned val)
{
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment(void)
{
    avm_push_envvalue(totalActuals);
    assert(code[pc].opcode == callfunc_v);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}
userfunc *avm_getfuncinfo(unsigned address){}

void execute_funcenter(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);
    totalActuals = 0;
    userfunc *funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

unsigned avm_get_envvalue(unsigned i)
{
    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction *unused)
{
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    while (++oldTop <= top)
    {
        avm_memcellclear(&stack[oldTop]);
    }
}

void avm_calllinfunc(char *id)
{
    library_func_t f = NULL;
    f = avm_getlibraryfunc(id);
    if (!f)
    {
        avm_error("unsupported lib func '%s' called!", id);
        executionFinished = 1;
    }
    else
    {
        avm_callsaveenvironment();
        topsp = top;
        totalActuals = 0;
        (*f)();
        if (!executionFinished)
        {
            execute_funcexit((instruction *)0);
        }
    }
}

unsigned avm_totalactuals(void)
{
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell *avm_getactual(unsigned i)
{
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void)
{
    unsigned n = avm_totalactuals();
    unsigned i;
    for (i = 0; i < n; ++i)
    {
        char *s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

void avm_push_table_arg(avm_table *t)
{
    stack[top].type = table_m;
    avm_tableincrefcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void execute_pusharg(instruction *instr)
{
    avm_memcell *arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

char *avm_tostring(avm_memcell *m)
{
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

double add_impl(double x, double y)
{
    return x + y;
}

double sub_impl(double x, double y)
{
    return x - y;
}

double mul_impl(double x, double y)
{
    return x * y;
}

double div_impl(double x, double y)
{
    return x / y;
}

double mod_impl(double x, double y)
{
    return ((unsigned)x) % ((unsigned)y);
}

void execute_arithmetic(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *mem1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *mem2 = avm_translate_operand(&instr->arg2, &bx);

    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(mem1 && mem2);

    if (mem1->type != number_m || mem2->type != number_m)
    {
        avm_error("not a number in arithmetic!", &code[pc]);
        executionFinished = 1;
    }
    else
    {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(mem1->data.numVal, mem2->data.numVal);
    }
}

void execute_add(instruction *instr) { execute_arithmetic(instr); }
void execute_sub(instruction *instr) { execute_arithmetic(instr); }
void execute_mul(instruction *instr) { execute_arithmetic(instr); }
void execute_div(instruction *instr) { execute_arithmetic(instr); }
void execute_mod(instruction *instr) { execute_arithmetic(instr); }
void execute_uminus(instruction *instr) { execute_arithmetic(instr); }

unsigned char number_tobool(avm_memcell *m)
{
    return m->data.numVal != 0;
}

unsigned char string_tobool(avm_memcell *m)
{
    return m->data.strVal[0] != 0;
}

unsigned char bool_tobool(avm_memcell *m)
{
    return m->data.boolVal;
}

unsigned char table_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char userfunc_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char libfunc_tobool(avm_memcell *m)
{
    return 1;
}

unsigned char nil_tobool(avm_memcell *m)
{
    return 0;
}

unsigned char undef_tobool(avm_memcell *m)
{
    return 0;
}

unsigned char avm_tobool(avm_memcell *m)
{
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

// copilot
void execute_jeq(instruction *instr)
{
    assert(instr->result.type == label_a);
    avm_memcell *mem1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *mem2 = avm_translate_operand(&instr->arg2, &bx);
    unsigned char result = 0;
    if (mem1->type == undef_m || mem2->type == undef_m)
    {
        avm_error("undef in equality!", &code[pc]);
        executionFinished = 1;
    }
    else if (mem1->type == nil_m || mem2->type == nil_m)
    {
        result = mem1->type == nil_m && mem2->type == nil_m;
    }
    else if (mem1->type == bool_m && mem2->type == bool_m)
    {
        result = mem1->data.boolVal == mem2->data.boolVal;
    }
    else if (mem1->type == number_m && mem2->type == number_m)
    {
        result = mem1->data.numVal == mem2->data.numVal;
    }
    else if (mem1->type == string_m && mem2->type == string_m)
    {
        result = !strcmp(mem1->data.strVal, mem2->data.strVal);
    }
    else if (mem1->type != mem2->type)
    {
        avm_error("%s == %s is illegal!", &code[pc]);
    }
    else
    {
        // equality check with  Αρκεί να
        // κάνετε dispatching ως
        // προς τον τύπο του mem1
    }
    if (!executionFinished && result)
    {
        pc = instr->result.val;
    }
}

void libfunc_typeof(void)
{
    unsigned n = avm_totalactuals();
    if (n != 1)
    {
        avm_error("one argument (not %d) expected in 'typeof'!", n);
    }
    else
    {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void execute_newtable(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    avm_memcellclear(lv);
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *t = avm_translate_operand(&instr->arg1, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(&instr->arg2, &ax);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i);
    avm_memcellclear(lv);
    lv->type = nil_m;
    if (t->type != table_m)
    {
        avm_error("illegal use of type %s as table!", &code[pc]);
    }
    else
    {
        avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
        if (content)
        {
            avm_assign(lv, content);
        }
        else
        {
            char *ts = avm_tostring(t);
            char *is = avm_tostring(i);
            avm_error("element %s not found in table %s!",&code[pc]);
            free(ts);
            free(is);
        }
    }
}

void avm_tablesetelem(avm_table *table, avm_memcell *index, avm_memcell *content){
    // prepei na doume test kai meta gia to content 
}

void execute_tablesetelem(instruction *instr)
{
    avm_memcell *t = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *c = avm_translate_operand(&instr->arg2, &bx);
    assert(t && &stack[AVM_STACKSIZE - 1] >= t && t > &stack[top]);
    assert(i && c);
    if (t->type != table_m)
    {
        avm_error("illegal use of type %s as table!", &code[pc]);
    }
    else
    {
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}
void avm_registerlibfunc(char *id, library_func_t addr){
    libfuncp *new = malloc(sizeof(libfuncp));
    new->id = strdup(id);
    new->address = addr;
    new->next = libfuncslist;
    libfuncslist = new;
}
void avm_initialize(void)
{
    //debug
    printf("in initialize\n");
    avm_initstack();
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);

    topsp = AVM_STACKSIZE-1;
    top   = AVM_STACKSIZE-1-totalglobalv;
    pc = 1;
}

void library_totalarguments(void)
{
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    avm_memcellclear(&retval);
    if (!p_topsp)
    {
        avm_error("totalarguments called outside a function!", &code[pc]);
        retval.type = nil_m;
    }
    else
    {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}
void get_binary(){
    FILE *bin = fopen("../avm_binary.abc", "rb");
    if (bin == NULL)
    {
        printf("Error opening the binary file\n");
        return;
    }

    unsigned magicnumber;
    fread(&magicnumber, sizeof(unsigned), 1, bin);
    if (magicnumber != 340200501) 
    {
        printf("Error: Magic number is not correct\n");
        printf("Magic number is: %u\n", magicnumber);
        return;
    }
    fprintf(stderr, "magic number %u\n", magicnumber);

    fread(&totalstringconsts, sizeof(int), 1, bin);
    fprintf(stderr, "total string %u\n", totalstringconsts);
    stringslist = malloc(totalstringconsts * sizeof(char *));
    for (int i = 0; i < totalstringconsts; i++)
    {
        int len;
        fread(&len, sizeof(int), 1, bin);
        stringslist[i] = malloc(len * sizeof(char));
        fread(stringslist[i], sizeof(char), len, bin);
    }

    fread(&totalnumconst, sizeof(int), 1, bin);
    numberconstslist = malloc(totalnumconst * sizeof(double));
    for(int i = 0; i < totalnumconst; i++)
    {
        fread(&numberconstslist[i], sizeof(double), 1, bin);
    }

    //fread(&totalglobalv, sizeof(int), 1, bin);  
    fread(&totallibfuncs, sizeof(unsigned int), 1, bin);
    fprintf(stderr, "total lib funcs %u\n", totallibfuncs);
    libfuncst = malloc(totallibfuncs * sizeof(char*));
    for(int i = 0; i < totallibfuncs; i++)
    {
        int len;
        fread(&len, sizeof(int), 1, bin);
        libfuncst[i] = malloc(len * sizeof(char));
        fread(libfuncst[i], sizeof(char), len, bin);
    }

    fread(&totaluserfuncs, sizeof(int), 1, bin);
    userFuncs = malloc(totaluserfuncs * sizeof(userfunc));
    fprintf(stderr, "total user funcs %u\n", totaluserfuncs);
    for(int i = 0; i < totaluserfuncs; i++)
    {
        int len;
        fread(&len, sizeof(int), 1, bin);
        userFuncs[i].id = malloc(len * sizeof(char));
        fread(userFuncs[i].id, sizeof(char), len, bin);
        fread(&userFuncs[i].address, sizeof(unsigned), 1, bin);
        fread(&userFuncs[i].localSize, sizeof(unsigned), 1, bin);
    }

    fread(&codeSize, sizeof(int), 1, bin);
    code = malloc(codeSize * sizeof(instruction));
    for(int i = 0; i < codeSize; i++)
    {
        fread(&code[i].opcode, sizeof(vm_opcode), 1, bin);
        fread(&code[i].result.type, sizeof(vmarg), 1, bin);
        fread(&code[i].result.val, sizeof(unsigned), 1, bin);
        fread(&code[i].arg1.type, sizeof(vmarg), 1, bin);
        fread(&code[i].arg1.val, sizeof(unsigned), 1, bin);
        fread(&code[i].arg2.type, sizeof(vmarg), 1, bin);
        fread(&code[i].arg2.val, sizeof(unsigned), 1, bin);
    }

    fclose(bin);

}

int main()
{
    //AVM_ENDING_PC = codeSize;
    avm_initialize();
    get_binary();
    //printf(" executionFinished %d : \n", executionFinished);
    while (executionFinished == 0)
    {
        execute_cycle();
    }

    avm_memcellclear(&ax);
    avm_memcellclear(&bx);
    avm_memcellclear(&cx);
    avm_memcellclear(&retval);
    return 0;
}   