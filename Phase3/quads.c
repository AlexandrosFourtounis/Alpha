#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "quads.h"


#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

 quad *quads = (quad *)0;
 unsigned total =0;
 unsigned int currQuad = 0;

unsigned int programVarOffset = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset = 0;
unsigned int scopeSpaceCounter = 1;

void expand(void){
    assert(total == currQuad);
    quad* p=(quad*)malloc(NEW_SIZE);
    if(quads){
        memcpy(p,quads,CURR_SIZE);
        free(quads);
    }
    quads=p;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned int label, unsigned int line){
    if(currQuad == total){
        expand();
    }
    quad* p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

scopespace_t currscopespace(void){
    if(scopeSpaceCounter == 1){
        return programVar;
    }
    else if(scopeSpaceCounter % 2 == 0){
        return formalArg;
    }
    else{
        return functionLocal;
    }
}

unsigned int currscopeoffset(void){
    switch(currscopespace()){
        case programVar: return programVarOffset;
        case functionLocal: return functionLocalOffset;
        case formalArg: return formalArgOffset;
        default: assert(0);
    }
}

void inccurrscopeoffset(void){
    switch(currscopespace()){
        case programVar: ++programVarOffset; break;
        case functionLocal: ++functionLocalOffset; break;
        case formalArg: ++formalArgOffset; break;
        default: assert(0);
    }
}

void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

int tempcounter = 0;
extern int scope;
extern int yylineno;

char *newtempname()
{
    char buffer[50];
    sprintf(buffer, "_t%d", tempcounter);
    return buffer;
}
void resettemp()
{
    tempcounter = 0;
}
void check_arith(expr *e, const char *context)
{
    if (e->type == constbool_e ||
        e->type == conststring_e ||
        e->type == nil_e ||
        e->type == newtable_e ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e)
    {
        printf(BOLD_RED"Illegal expr used in %s!"RESET, context);
        exit(-1);
    }
}

expr *newexpr(expr_t t)
{
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

expr *lvalue_expr(SymbolTableEntry *sym)
{
    assert(sym);
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->next = (expr *)0;
    e->sym = sym;
    switch (sym->type)
    {
    case GLOBAL:
    case LOCAL:
    case FORMAL:
        e = newexpr(var_e);
        break;
    case USERFUNC:
        e = newexpr(programfunc_e);
        break;
    case LIBFUNC:
        e = newexpr(libraryfunc_e);
        break;
    default:
        assert(0);
    }

    return e;
}



SymbolTableEntry *newtemp()
{
    char *name = newtempname();
    SymbolTableEntry *entry = lookup_in_scope(name, scope);
    if (entry == NULL)
    {
        SymbolType type = (scope == 0) ? GLOBAL : LOCAL;
        entry = insert(name, type, scope, yylineno);
        return entry;
    }
    else
    {
        return entry;
    }
}

void resetformalargsoffset(){
    formalArgOffset = 0;
}

void resetfunctionlocalsoffset(){
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned int n){
    switch (currscopespace()){
        case programVar    : programVarOffset = n; break;
        case functionLocal : functionLocalOffset = n; break;
        case formalArg     : formalArgOffset = n; break;
        default: assert(0);
    }
}

unsigned nextquadlabel(){
    return currQuad;
}

void patchlabel(unsigned int quadNo, unsigned int label){
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}