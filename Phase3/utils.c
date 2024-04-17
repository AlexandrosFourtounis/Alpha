#include "SymTable.h"
#include "quads.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
        e->type == boolexpr_e){
        printf("Illegal expr used in %s!", context);
        exit(-1);
        }
}

expr* lvalue_expr(symbol* sym)
{
    assert(sym);
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->next = (expr*)0;
    e->sym = sym;
    switch (sym->space)
    {
        case var_s:
            e->type = var_e;
            break;
        case programfunc_s:
            e->type = programfunc_e;
            break;
        case libraryfunc_s:
            e->type = libraryfunc_e;
            break;
        default:
            assert(0);
    }

    return e;
}

expr *newexpr(expr_t t){
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
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