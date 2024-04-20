#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "quads.h"


#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

quad *quads = (quad *)0;
unsigned int total =0;
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
    char temp[20]; // Buffer to hold the resulting string
    sprintf(temp, "_t%d", tempcounter);
    return strdup(temp);
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

unsigned int nextquadlabel(){
    return currQuad;
}

void patchlabel(unsigned int quadNo, unsigned int label){
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

expr* newexpr_conststring(char* s){
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr* emit_iftableitem(expr* e){
    if(e->type != tableitem_e) return e;
    else{
        expr* result = newexpr(var_e);
        result->sym = newtemp();
        emit(tablegetelem, e, e->index, result, 0, yylineno);
        return result;
    }
}

expr* member_item(expr* lv, char* name){
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

const char* opcode_to_string(iopcode opcode) {
    switch (opcode) {
        case assign: return "assign";
        case jump: return "jump";
        case add: return "add";
        case sub: return "sub";
        case mul: return "mul";
        case divv: return "divv";
        case mod: return "mod";
        case uminus: return "uminus";
        case and: return "and";
        case or: return "or";
        case not: return "not";
        case if_eq: return "if_eq";
        case if_noteq: return "if_noteq";
        case if_lesseq: return "if_lesseq";
        case if_greatereq: return "if_greatereq";
        case if_less: return "if_less";
        case if_greater: return "if_greater";
        case call: return "call";
        case param: return "param";
        case ret: return "ret";
        case getretval: return "getretval";
        case funcstart: return "funcstart";
        case funcend: return "funcend";
        case tablecreate: return "tablecreate";
        case tablegetelem: return "tablegetelem";
        case tablesetelem: return "tablesetelem";
        default: return "unknown opcode";
    }
}


void print_expression(expr *expr, FILE *f){
     if(!expr) {
        fprintf(f, "%-16s", "");
        return;
    }
    else if(expr->type == nil_e) {

        fprintf(f, "%-16s", "NIL");
        return;
    }
    
    switch(expr->type) {
        case constbool_e :
            fprintf(f, "%-16s", expr->boolConst ? "TRUE" : "FALSE");
            break;
        case constnum_e :
            fprintf(f, "%-16lf", expr->numConst);
            break;
        case conststring_e :
            fprintf(f, "%-16s", expr->strConst);
            break;
        case var_e :
            fprintf(f, "%-8s","var");
            break;
        default :
            fprintf(f, "%-8s", "default");
            break;
    }
}

void print_quads(){
    unsigned int i = 0U;
    FILE *f = fopen("quads.txt", "w");
    fprintf(f, "%-8s%-16s%-8s%-8s%-8s%-8s%-8s\n", "Quad", "Op", "Result", "Arg1", "Arg2", "Label", "Line");
    while(i < currQuad ){
        if(quads[i].op == assign || quads[i].op == uminus || quads[i].op == not){
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            //print_expression(quads[i].arg1, f);          
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        else if(quads[i].op == jump){
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));         
            fprintf(f, "%-8s%-8s%-8d%-8d\n", "", "", quads[i].label, quads[i].line);
        }
        else if(quads[i].op == getretval || quads[i].op == funcstart || quads[i].op == funcend || quads[i].op == ret || quads[i].op == tablecreate){
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);                    
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        else if(quads[i].op == if_eq || quads[i].op == if_greater || quads[i].op == if_greatereq || quads[i].op == if_less || quads[i].op == if_lesseq || quads[i].op == if_noteq || quads[i].op == and || quads[i].op == or) {
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));
            //print_expression(quads[i].arg1, f);
            //print_expression(quads[i].arg2, f);          
            fprintf(f, "%-8s%-8s%-8d%-8d\n", "", "", quads[i].label, quads[i].line);
        }
        else if(quads[i].op ==  add || quads[i].op == sub || quads[i].op == mul || quads[i].op == divv || quads[i].op == mod || quads[i].op == tablegetelem || quads[i].op == tablesetelem) {
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));
            //print_expression(quads[i].arg1, f);
            //print_expression(quads[i].arg2, f);          
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);       
        }
        else if(quads[i].op == param || quads[i].op == call){
            fprintf(f, "%-8d%-16s", i+1, opcode_to_string(quads[i].op));
            //print_expression(quads[i].arg1, f);          
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        i++;
    }    
}
