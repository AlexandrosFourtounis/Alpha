#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "quads.h"

#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

quad *quads = (quad *)0;
unsigned int total = 0;
unsigned int currQuad = 0;
unsigned int programVarOffset = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset = 0;
unsigned int scopeSpaceCounter = 1;
int tempcounter = 0;
extern int scope;
extern int yylineno;

void expand(void)
{
    assert(total == currQuad);
    quad *p = (quad *)malloc(NEW_SIZE);
    if (quads)
    {
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned int label, unsigned int line)
{
    if (currQuad == total)
    {
        expand();
    }
    quad *p     = malloc(sizeof(quad));
    assert(p);
    p = quads + currQuad++;
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

scopespace_t currscopespace(void)
{
    if (scopeSpaceCounter == 1)
        return programVar;
    else if (scopeSpaceCounter % 2 == 0)
        return formalArg;
    else
        return functionLocal;
}

unsigned int currscopeoffset(void)
{
    switch (currscopespace())
    {
    case programVar:
        return programVarOffset;
    case functionLocal:
        return functionLocalOffset;
    case formalArg:
        return formalArgOffset;
    default:
        assert(0);
    }
}

void inccurrscopeoffset(void)
{
    switch (currscopespace())
    {
    case programVar:
        ++programVarOffset;
        break;
    case functionLocal:
        ++functionLocalOffset;
        break;
    case formalArg:
        ++formalArgOffset;
        break;
    default:
        assert(0);
    }
}

void enterscopespace(void)
{
    ++scopeSpaceCounter;
}

void exitscopespace(void)
{
    assert(scopeSpaceCounter > 1);
    --scopeSpaceCounter;
}

char *newtempname()
{
    char temp[20]; // Buffer to hold the resulting string
    sprintf(temp, "_t%d", tempcounter++);
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
        printf(BOLD_RED "Illegal expr used in %s!" RESET, context);
        exit(-1);
    }
}

expr *newexpr(expr_t t)
{
    expr *e = (expr *)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = t;
    e->truelist = 0;
    e->falselist = 0;
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
        e->sym = sym;
        break;
    case USERFUNC:
        e = newexpr(programfunc_e);
        e->sym = sym;
        break;
    case LIBFUNC:
        e = newexpr(libraryfunc_e);
        e->sym = sym;
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

void resetformalargsoffset()
{
    formalArgOffset = 0;
}

void resetfunctionlocalsoffset()
{
    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned int n)
{
    switch (currscopespace())
    {
    case programVar:
        programVarOffset = n;
        break;
    case functionLocal:
        functionLocalOffset = n;
        break;
    case formalArg:
        formalArgOffset = n;
        break;
    default:
        assert(0);
    }
}

unsigned int nextquadlabel()
{
    return currQuad;
}

void patchlabel(unsigned int quadNo, unsigned int label)
{
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

expr *newexpr_conststring(char *s)
{
    expr *e = newexpr(conststring_e);
    e->strConst = strdup(s);
    e->sym = NULL;
    return e;
}

expr *newexpr_constnum(double x)
{
    expr *e = newexpr(constnum_e);
    e->sym = NULL;
    e->numConst = x;
    return e;
}

expr* newexpr_constbool(unsigned char b){
    expr* e = newexpr(constbool_e);
    e->sym = NULL;
    e->boolConst = b;
    return e;
}

expr *newexpr_bool(char *s)
{
    expr *e = newexpr(boolexpr_e);
    e->sym = NULL;
    printf("s: %s\n", s);
    if (strcmp(s, "true") == 0)
    {
        e->boolConst ="true";
    }
    else if (strcmp(s, "false") == 0)
        e->boolConst = "false";
    else
        assert(0);
    return e;
}

expr *newexpr_nil()
{
    expr *e = newexpr(nil_e);
    //e->strConst = strdup(s);
    e->sym = NULL;
    return e;
}

expr *emit_iftableitem(expr *e)
{
    if (e->type != tableitem_e)
        return e;
    else
    {
        expr *result = newexpr(var_e);
        result->sym = newtemp();
        emit(tablegetelem, e, e->index, result, 0, yylineno);
        return result;
    }
}

expr *emit_ifboolean(expr *e){
    if(e->type == boolexpr_e || e->type == constbool_e){
        patchlist(e->truelist, nextquadlabel());
        patchlist(e->falselist, nextquadlabel()+2);

        expr* tmp = newexpr(boolexpr_e);
        tmp->sym = newtemp();
        
        emit(assign, tmp, newexpr_constbool(1), NULL, -1, currQuad);
        emit(jump, NULL, NULL, NULL, nextquadlabel() + 2 , currQuad);
        emit(assign, tmp, newexpr_constbool(0), NULL, -1, currQuad);
        
        return tmp;
    }
    return e;
}

expr *member_item(expr *lv, char *name)
{
    lv = emit_iftableitem(lv);
    expr *ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

const char *opcode_to_string(iopcode opcode)
{
    switch (opcode)
    {
    case assign:
        return "assign";
    case jump:
        return "jump";
    case add:
        return "add";
    case sub:
        return "sub";
    case mul:
        return "mul";
    case divv:
        return "divv";
    case mod:
        return "mod";
    case uminus:
        return "uminus";
    case and:
        return "and";
    case or:
        return "or";
    case not:
        return "not";
    case if_eq:
        return "if_eq";
    case if_noteq:
        return "if_noteq";
    case if_lesseq:
        return "if_lesseq";
    case if_greatereq:
        return "if_greatereq";
    case if_less:
        return "if_less";
    case if_greater:
        return "if_greater";
    case call:
        return "call";
    case param:
        return "param";
    case ret:
        return "return";
    case getretval:
        return "getretval";
    case funcstart:
        return "funcstart";
    case funcend:
        return "funcend";
    case tablecreate:
        return "tablecreate";
    case tablegetelem:
        return "tablegetelem";
    case tablesetelem:
        return "tablesetelem";
    default:
        return "unknown opcode";
    }
}

void print_expression(expr *expr, FILE *f)
{
    if (!expr)
    {
        fprintf(f, "%-16s", "");
        return;
    }
    if (expr == NULL) {
        fprintf(f, "NULL expression\n");
        return;
    }
    printf("expr: %p\n", (void *)expr);
     if (expr != NULL && expr->type == nil_e)
    {
        fprintf(f, "%-8s", "NIL");
        return;
    }

    switch (expr->type)
    {
    case boolexpr_e:
        if (expr->boolConst)
            fprintf(f, "%-8s", "true");
        else
            fprintf(f, "%-8s", "false");
        break;
    case constnum_e:
        fprintf(f, "%-8.2f", expr->numConst);
        break;
    case constbool_e:
        if(expr->boolConst)
            fprintf(f, "%-8s", "true");
        else
            fprintf(f, "%-8s", "false");
        break;
    case conststring_e:
        fprintf(f, "%-8s", expr->strConst);
        break;
    case programfunc_e:
        fprintf(f, "%-8s", expr->sym->value.funcVal->name);
        break;
    case libraryfunc_e:
        fprintf(f, "%-8s", expr->sym->value.funcVal->name);
        break;
    case arithexpr_e:
        if(expr->sym->value.varVal)
        {
            fprintf(f, "%-8s", expr->sym->value.varVal->name);
        }
        else
        {
            fprintf(f, "%-8s", "var");
        }
        break;
    
    case assignexpr_e:
        if(expr->sym->value.varVal)
        {
            fprintf(f, "%-8s", expr->sym->value.varVal->name);
        }
        else
        {
            fprintf(f, "%-8s", "var");
        }
        break;
    case var_e:
        if (expr->sym && expr->sym->value.varVal)
        {
            fprintf(f, "%-8s", expr->sym->value.varVal->name);
        }
        else
        {
            fprintf(f, "%-8s", "var");
        }
        break;
    default:
        fprintf(f, "%-8s", expr->strConst);
        break;
    }
}

void print_quads()
{
    unsigned int i = 0U;
    FILE *f = fopen("quads.txt", "w");
    fprintf(f, "%-8s%-16s%-8s%-8s%-8s%-8s%-8s\n", "QUAD", "OP", "RESULT", "ARG1", "ARG2", "LABEL", "LINE");

    while (i < currQuad)
    {
        if (quads[i].op == assign || quads[i].op == uminus || quads[i].op == not )
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            print_expression(quads[i].arg1, f);
            //print_expression(quads[i].arg2, f);
             fprintf(f, "%-8s", "");
            fprintf(f, "%-8d%-8d", quads[i].label, quads[i].line);
            fprintf(f, "\n");
        }
        else if (quads[i].op == jump )
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            fprintf(f, "%-8s%-8s%-8s%-8d%-8d\n","", "", "", quads[i].label, quads[i].line);
        }

        else if(quads[i].op == ret){
            
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n","", "", "", quads[i].line);
        }
        else if (quads[i].op == getretval || quads[i].op == funcstart || quads[i].op == funcend  || quads[i].op == tablecreate)

        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].arg1, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        else if (quads[i].op == if_eq || quads[i].op == if_greater || quads[i].op == if_greatereq || quads[i].op == if_less || quads[i].op == if_lesseq || quads[i].op == if_noteq || quads[i].op == and || quads[i].op == or)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            fprintf(f,"%-8s", "");
            print_expression(quads[i].arg1, f);
            print_expression(quads[i].arg2, f);
            fprintf(f, "%-8d%-8d\n", quads[i].label, quads[i].line);
            
        }
        else if (quads[i].op == add || quads[i].op == sub || quads[i].op == mul || quads[i].op == divv || quads[i].op == mod || quads[i].op == tablegetelem || quads[i].op == tablesetelem)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            print_expression(quads[i].arg1, f);
            print_expression(quads[i].arg2, f);
            fprintf(f, "%-8d%-8d\n", quads[i].label, quads[i].line);
        }
        else if (quads[i].op == param || quads[i].op == call)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].arg1, f);
            fprintf(f, "%-8s%-8s%-8d\n", "", "", quads[i].line);
        }
        else if (quads[i].op == getretval ){
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            fprintf(f, "%-8s%-8s%-8d\n", "", "", quads[i].line);
        }
        i++;
    }
}

expr *Manage_operations(expr *arg1, iopcode op, expr *arg2)
{
    assert(arg1);
    assert(arg2);

    check_arith(arg1, (const char *)"Manage_operations");
    check_arith(arg2, (const char *)"Manage_operations");

    expr *result = NULL;
    SymbolTableEntry *temp;

    // if (arg1->sym && arg1->sym->value.varVal && arg1->sym->value.varVal->name)
    // {
    //     printf("arg1: %s\n", arg1->sym->value.varVal->name);
    // }
    // else
    // {
    //     printf("arg1: %s\n", "NULL");
    // }

    // if (arg2->sym && arg2->sym->value.varVal && arg2->sym->value.varVal->name)
    // {
    //     printf("arg2: %s\n", arg2->sym->value.varVal->name);
    // }
    // else
    // {
    //     printf("arg2: %s\n", "NULL");
    // }

    if (arg1->sym && arg1->sym->type < 2 && arg1->sym->value.varVal->name[0] == '_') // in case of tmp
    {
        temp = arg1->sym;
    }
    else if (arg2->sym && arg2->sym->type < 2 && arg2->sym->value.varVal->name[0] == '_')
    {
        temp = arg2->sym;
    }
    else
    {
        temp = newtemp(); // create new tmp variable
    }

    result = lvalue_expr(temp);
    result->sym = temp;

    switch (op)
    {
    case add:
        emit(add, arg1, arg2, result, 0, yylineno);
        break;
    case sub:
        emit(sub, arg1, arg2, result, 0, yylineno);
        break;
    case mul:
        emit(mul, arg1, arg2, result, 0, yylineno);
        break;
    case divv:
        emit(divv, arg1, arg2, result, 0, yylineno);
        break;
    case mod:
        emit(mod, arg1, arg2, result, 0, yylineno);
        break;
    default:
        printf("Invalid operation\n");
        exit(-1);
    }
    return result;
}

expr *Manage_comparisonopers(expr *arg1, char *op, expr *arg2)
{
    assert(arg1);
    assert(arg2);

    expr *tmp = newexpr(boolexpr_e);
    // tmp->sym = newtemp();

    // ta lines prepei na diorthothoun gia na exoun to currQuad
    switch (op[0])
    {
    case '=':
        tmp->type = boolexpr_e;
        emit(if_eq, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
        emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        tmp->truelist = newlist(nextquadlabel());
        tmp->falselist = newlist(nextquadlabel()+1);
        break;
    case '!':
        tmp->type = boolexpr_e;
        emit(if_noteq, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
        emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        tmp->truelist = newlist(nextquadlabel());
        tmp->falselist = newlist(nextquadlabel()+1);
        break;
    case '<':
        tmp->type = boolexpr_e;
        if (strcmp(op, "<") == 0)
        {
            emit(if_less, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        }
        else if (strcmp(op, "<=") == 0)
        {
            emit(if_lesseq, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        }
        tmp->truelist = newlist(nextquadlabel());
        tmp->falselist = newlist(nextquadlabel()+1);
        break;
    case '>':
        tmp->type = boolexpr_e;
        if (strcmp(op, ">") == 0)
        {
            emit(if_greater, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        }
        else if (strcmp(op, ">=") == 0)
        {
            emit(if_greatereq, arg1, arg2, NULL, nextquadlabel()+2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel()+3, yylineno);
        }
        tmp->truelist = newlist(nextquadlabel());
        tmp->falselist = newlist(nextquadlabel()+1);
        break;
    default:
        printf("Invalid comparison operator\n");
        exit(-1);
    }
    return tmp;
}

expr *make_call(expr *lv, expr *reversed_elist){
    expr *func = emit_iftableitem(lv);
    while(reversed_elist){
        emit(param, reversed_elist, NULL, NULL, 0U, yylineno);
        reversed_elist = reversed_elist->next;  
    }
    emit(call, func, NULL, NULL, 0U, yylineno);
    expr *result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval, NULL, NULL, result, 0U, yylineno);
    return result;
}

reversed_list *createExprNode(expr *item){
    reversed_list *node = malloc(sizeof(reversed_list));
    node->item = item;
    node->next = NULL;
    return node;
}
void addToExprList(reversed_list **head, expr *item){
    reversed_list *node = createExprNode(item);
    node->next = *head;
    *head = node;
}

reversed_list *get_last(reversed_list *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    while (head->next != NULL)
    {
        head = head->next;
    }
    return head;
}

int mergelist(int l1, int l2)
{
    if (!l1)
        return l2;
    else if (!l2)
        return l1;
    else
    {
        int i = l1;
        while (quads[i].label)
            i = quads[i].label;
        quads[i].label = l2;
        return l1;
    }
}

void patchlist(int list, int label){
    while(list) {
    {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
    }
}

//fixed
stmt_struct* make_stmt () { 
    stmt_struct *s = malloc(sizeof(stmt_struct));
    if (s == NULL) {
        fprintf(stderr, "Failed to allocate memory for stmt_struct\n");
        exit(EXIT_FAILURE);
    }
    s->breaklist = 0;
    s->contlist = 0;
    return s;
}


int newlist(int i){
    quads[i].label = 0; 
    return i; 
}

int true_test(expr* arg){
    //puts("I AM TRUE TESTING");
    if(arg == NULL){
        //puts("I AM HERE");
        return 0;
    }
    else if(arg->type == boolexpr_e) {
        //puts("I AM HERE");
        return 0;
    }
    
    
    //arg->type = boolexpr_e;
    //if(arg->type != constbool_e){
        arg->type = boolexpr_e;
    //}
    
    emit(if_eq, arg, newexpr_constbool(1),NULL, 0, currQuad);
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    // printf("%d\n", nextquad()-2);
    // printf("%d\n", nextquad()-1);
    arg->truelist = newlist(nextquadlabel()-2);
    arg->falselist = newlist(nextquadlabel()-1);
    return 1;
}
/*
expr* Manage_boolexpr(expr* arg1,iopcode op, expr* arg2, unsigned int Mlabel){
    //fprintf(yacc_out,"boolexpr -> expr %s expr\n", op);
    expr* tmp_expr=newexpr(boolexpr_e);
    //tmp_expr->sym = NULL;
    //tmp_expr->sym = new_temp(); // create new tmp variable
    // expr* tmp_expr = lvalue_to_expr(tmp); // make it an lvalue expr
    // tmp_expr->type = boolexpr_e;
    
    switch (op){
        case or:
        //emit(or, tmp_expr, arg1, arg2, -1, currQuad);
        //if(true_test(arg1)) Mlabel += 2;
        //true_test(arg2);
        tmp_expr->type = boolexpr_e;
        patchlist(arg1->falselist, Mlabel);
        tmp_expr->truelist = mergelist(arg1->truelist, arg2->truelist);
        tmp_expr->falselist = arg2->falselist;
        break;
    case and:
        //emit(and, tmp_expr, arg1, arg2, -1, currQuad);
        //if(true_test(arg1)) Mlabel += 2;
        //true_test(arg2);
        tmp_expr->type = boolexpr_e;
        //printf("Mlabel = %d\n", Mlabel);
        patchlist(arg1->truelist, Mlabel);
        tmp_expr->truelist = arg2->truelist;
        tmp_expr->falselist = mergelist(arg1->falselist, arg2->falselist);
        break;
    default:
        printf("Invalid operator\n");
        return NULL;
        break;
    }
    
    return tmp_expr;
} */