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
int test;
extern int yylineno;
char *curr_temp_name = NULL;
FuncStack *funcstack = NULL;

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
    quad *p = malloc(sizeof(quad));
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
    curr_temp_name = strdup(temp);
    return strdup(temp);
}

SymbolTableEntry *curr_temp()
{
    return lookup(curr_temp_name, scope);
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
    quads[quadNo].label = label + 1;
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

expr *newexpr_constbool(unsigned char b)
{
    expr *e = newexpr(constbool_e);
    e->sym = NULL;
    e->boolConst = b;
    return e;
}

expr *newexpr_bool(char *s)
{
    expr *e = newexpr(boolexpr_e);
    e->sym = NULL;
    // printf("s: %s\n", s);
    if (strcmp(s, "true") == 0)
    {
        e->boolConst = "true";
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
    // e->strConst = strdup(s);
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

expr *backpatching(expr *e)
{
    if (e->type == boolexpr_e || e->type == constbool_e)
    {
        patchlist(e->truelist, nextquadlabel());
        patchlist(e->falselist, nextquadlabel() + 2);

        expr *tmp = newexpr(var_e);
        tmp->sym = newtemp();

        emit(assign, newexpr_constbool(1), NULL, tmp, 0, currQuad);
        emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, currQuad);
        emit(assign, newexpr_constbool(0), NULL, tmp, 0, currQuad);

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
        fprintf(f, "%-8s", "");
        return;
    }
    if (expr == NULL)
    {
        fprintf(f, "NULL expression\n");
        return;
    }
    // printf("expr: %p\n", (void *)expr);
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
        if (expr->boolConst)
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
        if (expr->sym->value.varVal)
        {
            fprintf(f, "%-8s", expr->sym->value.varVal->name);
        }
        else
        {
            fprintf(f, "%-8s", "var");
        }
        break;

    case assignexpr_e:
        if (expr->sym->value.varVal)
        {
            fprintf(f, "%-8s", expr->sym->value.varVal->name);
        }
        else
        {
            fprintf(f, "%-8s", "var");
        }
        break;
    case tableitem_e:
        fprintf(f, "%-8s", expr->sym->value.varVal->name);
        break;
    case newtable_e:
        fprintf(f, "%-8s", expr->sym->value.varVal->name);
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
    fprintf(f, "------------------------------------------------------------\n");

    while (i < currQuad)
    {
        if (quads[i].op == assign || quads[i].op == uminus || quads[i].op == not )
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            print_expression(quads[i].arg1, f);
            // print_expression(quads[i].arg2, f);
            fprintf(f, "%-8s", "");
            fprintf(f, "%-8s%-8d", "", quads[i].line);
            fprintf(f, "\n");
        }
        else if (quads[i].op == jump)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            fprintf(f, "%-8s%-8s%-8s%-8d%-8d\n", "", "", "", quads[i].label, quads[i].line);
        }

        else if (quads[i].op == ret || quads[i].op == tablecreate)
        {

            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        else if (quads[i].op == funcstart || quads[i].op == funcend)

        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].arg1, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }
        else if (quads[i].op == if_eq || quads[i].op == if_greater || quads[i].op == if_greatereq || quads[i].op == if_less || quads[i].op == if_lesseq || quads[i].op == if_noteq || quads[i].op == and || quads[i].op == or)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            fprintf(f, "%-8s", "");
            print_expression(quads[i].arg1, f);
            print_expression(quads[i].arg2, f);
            fprintf(f, "%-8d%-8d\n", quads[i].label, quads[i].line);
        }
        else if (quads[i].op == add || quads[i].op == sub || quads[i].op == mul || quads[i].op == divv || quads[i].op == mod || quads[i].op == tablegetelem)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].result, f);
            print_expression(quads[i].arg1, f);
            print_expression(quads[i].arg2, f);

            fprintf(f, "%-8s%-8d\n", "", quads[i].line);
        }
        else if (quads[i].op == tablesetelem)
        {
            if (quads[i].line > 2000)
            {
                fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
                print_expression(quads[i].arg2, f);
                print_expression(quads[i].arg1, f);
                print_expression(quads[i].result, f);
                fprintf(f, "%-8s%-8d\n", "", quads[i].line - 2000);
            }
            else if (quads[i].line > 1000)
            {
                fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
                print_expression(quads[i].arg1, f);
                print_expression(quads[i].arg2, f);
                print_expression(quads[i].result, f);
                fprintf(f, "%-8s%-8d\n", "", quads[i].line - 1000);
            }
            else
            {
                fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
                print_expression(quads[i].result, f);
                print_expression(quads[i].arg1, f);
                print_expression(quads[i].arg2, f);
                fprintf(f, "%-8s%-8d\n", "", quads[i].line);
            }
        }
        else if (quads[i].op == param || quads[i].op == call)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            print_expression(quads[i].arg1, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
        }

        else if (quads[i].op == getretval)
        {
            fprintf(f, "%-8d%-16s", i + 1, opcode_to_string(quads[i].op));
            struct expr *tmp = newexpr(var_e);
            tmp->sym = newtemp();
            print_expression(tmp, f);
            fprintf(f, "%-8s%-8s%-8s%-8d\n", "", "", "", quads[i].line);
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

    temp = (arg1->sym && arg1->sym->type < 2 && arg1->sym->value.varVal->name[0] == '_') ? arg1->sym : (arg2->sym && arg2->sym->type < 2 && arg2->sym->value.varVal->name[0] == '_') ? arg2->sym
                                                                                                                                                                                     : newtemp();

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

    if (arg1->type == boolexpr_e)
    {
        arg1 = backpatching(arg1);
    }
    if (arg2->type == boolexpr_e)
    {
        arg2 = backpatching(arg2);
    }

    // ta lines prepei na diorthothoun gia na exoun to currQuad
    switch (op[0])
    {
    case '=':
        tmp->type = boolexpr_e;
        emit(if_eq, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
        emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        tmp->truelist = newlist(nextquadlabel() - 2);
        // printf("truelist%d\n", tmp->truelist);
        tmp->falselist = newlist(nextquadlabel() - 1);
        // printf("falselist%d\n", tmp->falselist);
        break;
    case '!':
        tmp->type = boolexpr_e;
        emit(if_noteq, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
        emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        tmp->truelist = newlist(nextquadlabel() - 2);
        // printf("truelist%d\n", tmp->truelist);
        tmp->falselist = newlist(nextquadlabel() - 1);
        // printf("falselist%d\n", tmp->falselist);
        break;
    case '<':
        tmp->type = boolexpr_e;
        if (strcmp(op, "<") == 0)
        {
            emit(if_less, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        }
        else if (strcmp(op, "<=") == 0)
        {
            emit(if_lesseq, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        }
        tmp->truelist = newlist(nextquadlabel() - 2);
        // printf("truelist%d\n", tmp->truelist);
        tmp->falselist = newlist(nextquadlabel() - 1);
        // printf("falselist%d\n", tmp->falselist);
        break;
    case '>':
        tmp->type = boolexpr_e;
        if (strcmp(op, ">") == 0)
        {
            emit(if_greater, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        }
        else if (strcmp(op, ">=") == 0)
        {
            emit(if_greatereq, arg1, arg2, NULL, nextquadlabel() + 2, yylineno);
            emit(jump, NULL, NULL, NULL, nextquadlabel() + 3, yylineno);
        }
        tmp->truelist = newlist(nextquadlabel() - 2);
        // printf("truelist%d\n", tmp->truelist);
        tmp->falselist = newlist(nextquadlabel() - 1);
        // printf("falselist%d\n", tmp->falselist);
        break;
    default:
        printf("Invalid comparison operator\n");
        exit(-1);
    }
    return tmp;
}

expr *reverse_elist(expr *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    expr *prev = NULL;
    expr *current = head;
    expr *next = NULL;
    while (current != NULL)
    {
        next = current->next; // store the next node
        current->next = prev; // reverse the link
        prev = current;       // move the prev and current one step forward
        current = next;
    }
    head = prev; // finally, make the last node as head
    return head;
}

expr *make_call(expr *lv, expr *reversed_elist)
{
    expr *func = emit_iftableitem(lv);
    if (reversed_elist != NULL)
        reversed_elist = reverse_elist(reversed_elist); // reverse the elist

    while (reversed_elist)
    {
        emit(param, reversed_elist, NULL, NULL, 0U, yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(call, func, NULL, NULL, 0U, yylineno);
    expr *result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval, NULL, NULL, result, 0U, yylineno);
    return result;
}

reversed_list *createExprNode(expr *item)
{
    reversed_list *node = malloc(sizeof(reversed_list));
    node->item = item;
    node->next = NULL;
    return node;
}
void addToExprList(reversed_list **head, expr *item)
{
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

void patchlist(int list, int label)
{
    while (list)
    {
        {
            int next = quads[list].label;
            quads[list].label = label + 1;
            list = next;
        }
    }
}

// fixed
stmt_struct *make_stmt()
{
    stmt_struct *s = malloc(sizeof(stmt_struct));
    if (s == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for stmt_struct\n");
        exit(EXIT_FAILURE);
    }
    s->breaklist = 0;
    s->contlist = 0;
    return s;
}

int newlist(int i)
{
    quads[i].label = 0;
    return i;
}

int true_test(expr *arg)
{

    if (arg == NULL)
    {
        return 0;
    }
    else if (arg->type == boolexpr_e)
    {
        return 0;
    }
    // arg->type = boolexpr_e;
    // if(arg->type != constbool_e){
    arg->type = boolexpr_e;
    //}
    emit(if_eq, arg, newexpr_constbool(1), NULL, 0, currQuad);
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    // printf("%d\n", nextquad()-2);
    // printf("%d\n", nextquad()-1);
    arg->truelist = newlist(nextquadlabel() - 2);
    arg->falselist = newlist(nextquadlabel() - 1);
    return 1;
}

/*Phase 4*/

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
    generate_NOP};

void initialize_funcstack(FuncStack *fs)
{
    fs->top = -1;
}

int isEmpty_funcstack(FuncStack *fs)
{
    return (fs->top == -1);
}

int isFull_funcstack(FuncStack *fs)
{
    return (fs->top == MAX_SIZE - 1);
}

void push_funcstack(FuncStack *fs, SymbolTableEntry *value)
{
    if (isFull_funcstack(fs))
    {
        printf("Error: funcstack overflow\n");
        return;
    }
    fs->arr[fs->top + 1] = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    if (fs->arr[fs->top + 1] == NULL)
    {
        printf("Error: memory allocation failed\n");
        return;
    }
    fs->arr[++fs->top] = value;
}

SymbolTableEntry *pop_funcstack(FuncStack *fs)
{
    if (isEmpty_funcstack(fs))
    {
        printf("Error: funcstack underflow\n");
        return -1;
    }
    return fs->arr[funcstack->top--];
}

SymbolTableEntry *top_funcstack(FuncStack *fs)
{
    if (isEmpty(fs))
    {
        printf("Error: funcstack is empty\n");
        return -1;
    }
    return fs->arr[fs->top];
}
double *numConsts = (double *)0;
unsigned int totalNumConsts = 0;
char **stringConsts = (char **)0;
unsigned int totalStringConsts = 0;
char **namedLibfuncs = (char **)0;
unsigned int totalNamedLibfuncs = 0;
unsigned int totalUserFuncs = 0;
userfunc *userFuncs = (userfunc *)0;
unsigned int curr_userfuncs = 0;

void reset_operand(vmarg *arg)
{
    arg->val = 0;
}

unsigned int consts_newstring(char *s){
    if(totalStringConsts == 0){
        stringConsts = (char **)malloc(1024 * sizeof(char *));
    }
    if (totalStringConsts % 1024 == 0)
        stringConsts = realloc(stringConsts, sizeof(*stringConsts) * (totalStringConsts + 1024));
    stringConsts[totalStringConsts++] = strdup(s);
    return totalStringConsts - 1;
}

unsigned int consts_newnumber(double n){
    if(totalNumConsts == 0){
        numConsts = (double *)malloc(1024 * sizeof(double));
    }
    if (totalNumConsts % 1024 == 0)
        numConsts = realloc(numConsts, sizeof(*numConsts) * (totalNumConsts + 1024));
    numConsts[totalNumConsts++] = n;
    return totalNumConsts - 1;
}

unsigned int libfuncs_newused(char *s){
    if(totalNamedLibfuncs == 0){
        namedLibfuncs = (char **)malloc(1024 * sizeof(char *));
    }
    if (totalNamedLibfuncs % 1024 == 0)
        namedLibfuncs = realloc(namedLibfuncs, sizeof(*namedLibfuncs) * (totalNamedLibfuncs + 1024));
    namedLibfuncs[totalNamedLibfuncs++] = strdup(s);
    return totalNamedLibfuncs - 1;
}

void
    make_operand(expr *e, vmarg *arg)
{
    switch (e->type)
    {

    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case newtable_e:
    {
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space)
        {
        case programVar:
            arg->type = global_a;
            break;
        case functionLocal:
            arg->type = local_a;
            break;
        case formalArg:
            arg->type = formal_a;
            break;
        default:
            assert(0);
        }
        break;
    }
    case constbool_e:
    {
        arg->val = e->boolConst;
        arg->type = bool_a;
        break;
    }
    case conststring_e:
    {
        arg->val = consts_newstring(e->strConst);
        arg->type = string_a;
        break;
    }
    case constnum_e:
    {
        arg->val = consts_newnumber(e->numConst);
        arg->type = number_a;
        break;
    }
    case nil_e:
    {
        arg->type = nil_a;
        break;
    }
    case programfunc_e:
    {
        arg->val = e->sym->taddress;
        arg->type = userfunc_a;
        break;
    }
    case libraryfunc_e:
    {
        arg->val = libfuncs_newused(e->sym->value.funcVal->name);
        arg->type = libfunc_a;
        break;
    }
    default:
        assert(0);
    }
}

void make_numberoperand(vmarg *arg, double val)
{
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}
void make_booloperand(vmarg *arg, unsigned val)
{
    arg->val = val;
    arg->type = bool_a;
}
void make_retvaloperand(vmarg *arg)
{
    arg->type = retval_a;
}



incomplete_jump *ij_head = (incomplete_jump *)0;
unsigned int ij_total = 0;
unsigned int curr_instr = 0;
unsigned int totalInstr = 0;
instruction *instructions = (instruction *)0;

void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress)
{
    incomplete_jump *new = (incomplete_jump *)malloc(sizeof(incomplete_jump));
    new->instrNo = instrNo;
    new->iaddress = iaddress;
    new->next = ij_head;
    ij_head = new;
    ij_total++;
}

void patch_incomplete_jumps()
{ /*INCOMPLETE*/
    incomplete_jump *current = ij_head;
    while (current)
    {
        if (current->iaddress == 0)
        {
            current->iaddress = currQuad;
        }
        else
        {
            quads[current->instrNo].arg1->sym->iaddress = currQuad;
        }
        current = current->next;
    }
}

void generate(void)
{
    for (unsigned int i = 0; i < total; i++)
    {
        (*generators[quads[i].op])(quads + i);
    }
}

void emit_instruction(instruction *t)
{
    if (curr_instr == totalInstr)
    {
        /*expand size*/
        assert(totalInstr == curr_instr);
        instruction *temp = (instruction *)malloc(1024 * sizeof(instruction) + (totalInstr * sizeof(instruction)));
        if (instructions)
        {
            memcpy(temp, instructions, totalInstr * sizeof(instruction));
            free(instructions);
        }
        instructions = temp;
        totalInstr += 1024;
    }
    instruction *tmp = instructions + curr_instr++;
    tmp->opcode = t->opcode;
    tmp->result = t->result;
    tmp->arg1 = t->arg1;
    tmp->arg2 = t->arg2;
    tmp->srcLine = t->srcLine;
}

unsigned int nextinstrlabel()
{
    return curr_instr;
}

void generate_op(vm_opcode op, quad *q)
{
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = op;
    t->srcLine = q->line;

    make_operand(q->arg1, &t->arg1);
    make_operand(q->arg2, &t->arg2);
    make_operand(q->result, &t->result);
    q->taddress = nextinstrlabel();
    emit_instruction(t);
}

void generate_ADD(quad *q)
{
    generate_op(add_v, q);
}

void generate_SUB(quad *q)
{
    generate_op(sub_v, q);
}
void generate_MUL(quad *q)
{
    generate_op(mul_v, q);
}
void generate_DIV(quad *q)
{
    generate_op(div_v, q);
}
void generate_MOD(quad *q)
{
    generate_op(mod_v, q);
}
void generate_TABLECREATE(quad *q) { generate_op(newtable_v, q); }

void generate_TABLEGETELEM(quad *q) { generate_op(tablegetelem_v, q); }

void generate_TABLESETELEM(quad *q) { generate_op(tablesetelem_v, q); }

void generate_ASSIGN(quad *q) { generate_op(assign_v, q); }

void generate_NOP(quad *q)
{
    instruction *t = (instruction *)malloc(sizeof(instruction));
    t->opcode = nop_v;
    t->srcLine = q->line;

    emit_instruction(t);
}

void generate_relational(vm_opcode op, quad *q)
{
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = op;
    t->srcLine = q->line;

    make_operand(q->arg1, &t->arg1);
    make_operand(q->arg2, &t->arg2);
    t->result.type = label_a;
    if (q->label < currQuad)
    {
        t->result.val = quads[q->label].taddress;
    }
    else
    {
        add_incomplete_jump(nextinstrlabel(), q->label);
    }
    q->taddress = nextinstrlabel();
    emit_instruction(t);
}

void generate_JUMP(quad *q)
{
    generate_relational(jump_v, q);
}

void generate_IF_EQ(quad *q)
{
    generate_relational(jeq_v, q);
}

void generate_IF_NOTEQ(quad *q)
{
    generate_relational(jne_v, q);
}

void generate_IF_GREATER(quad *q)
{
    generate_relational(jgt_v, q);
}

void generate_IF_GREATEREQ(quad *q)
{
    generate_relational(jge_v, q);
}

void generate_IF_LESS(quad *q)
{
    generate_relational(jlt_v, q);
}

void generate_IF_LESSEQ(quad *q)
{
    generate_relational(jle_v, q);
}

void generate_NOT(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->srcLine = q->line;

    t->opcode = jeq_v;
    make_operand(q->arg1, &t->arg1);
    make_booloperand(&t->arg2, 0);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 3;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 0);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 2;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 1);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);
}

void generate_OR(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->srcLine = q->line;

    t->opcode = jeq_v;
    make_operand(q->arg1, &t->arg1);
    make_booloperand(&t->arg2, 1);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 4;
    emit_instruction(t);

    make_operand(q->arg2, &t->arg1);
    t->result.val = nextinstrlabel() + 3;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 0);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 2;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 1);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);
}

void generate_AND(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->srcLine = q->line;

    t->opcode = jeq_v;
    make_operand(q->arg1, &t->arg1);
    make_booloperand(&t->arg2, 0);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 4;
    emit_instruction(t);

    make_operand(q->arg2, &t->arg1);
    t->result.val = nextinstrlabel() + 3;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 1);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstrlabel() + 2;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, 0);
    reset_operand(&t->arg2);
    make_operand(q->result, &t->result);
    emit_instruction(t);
}

void generate_PARAM(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = pusharg_v;
    t->srcLine = q->line;

    make_operand(q->arg1, &t->arg1);
    emit_instruction(t);
}

void generate_CALL(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = callfunc_v;
    t->srcLine = q->line;

    make_operand(q->arg1, &t->arg1);
    // reset_operand(&t->arg2);
    // reset_operand(&t->result);
    emit_instruction(t);
}

void generate_GETRETVAL(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = assign_v;
    t->srcLine = q->line;
    make_operand(q->result, &t->result);
    make_retvaloperand(&t->arg1);
    emit_instruction(t);
}

void generate_FUNCSTART(quad *q)
{
    SymbolTableEntry *sym = q->result->sym;
    sym->taddress = nextinstrlabel();
    q->taddress = nextinstrlabel();

    /*ADD to userfuncs new node*/
    /*expand size*/
    assert(totalUserFuncs == curr_userfuncs);
    userfunc *temp = (userfunc *)malloc(1024 * sizeof(userfunc) + (totalUserFuncs * sizeof(userfunc)));
    if (userFuncs)
    {
        memcpy(temp, userFuncs, totalUserFuncs * sizeof(userfunc));
        free(userFuncs);
    }
    userFuncs = temp;
    totalUserFuncs += 1024;

    userFuncs[curr_userfuncs].id = sym->value.funcVal->name;
    userFuncs[curr_userfuncs].address = sym->taddress;
    userFuncs[curr_userfuncs].localSize = sym->totalLocals;

    push_funcstack(funcstack, sym);

    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = enterfunc_v;
    t->srcLine = q->line;
    make_operand(q->result, &t->result);
    emit_instruction(t);
}



void generate_RET(quad *q)
{
    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = assign_v;
    t->srcLine = q->line;
    make_retvaloperand(&t->result);
    make_operand(q->arg1, &t->arg1);
    emit_instruction(t);

    SymbolTableEntry *f = top_funcstack(funcstack);

    if (!f)
    {
        fprintf(stderr, "Error:  stack returned NULL top\n");
        exit(EXIT_FAILURE);
    }
    returnList *rl = f->value.funcVal->returnList;
    if (!rl)
    {
        rl = malloc(sizeof(returnList));
        rl->ret = nextinstrlabel();
        rl->next = NULL;
        f->value.funcVal->returnList = rl;
    }
    else
    {
        while (rl->next)
        {
            rl = rl->next;
        }
        rl->ret = nextinstrlabel();
    }

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    emit_instruction(t);
}
void backpatch_ret_list(returnList *list, unsigned int label)
{
    if (!list)
    {
        fprintf(stderr, "cannot patch empty return list\n");
        exit(EXIT_FAILURE);
    }
    while (list)
    {
        instructions[list->ret].result.val = label;
        list = list->next;
    }
}

void generate_FUNCEND(quad *q)
{
    SymbolTableEntry *sym = pop_funcstack(funcstack);

    backpatch_ret_list(sym->value.funcVal->returnList, nextinstrlabel());

    q->taddress = nextinstrlabel();
    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = exitfunc_v;
    t->srcLine = q->line;

    make_operand(q->result, &t->result);
    emit_instruction(t);
}

void generate_UMINUS(quad *q)
{

    instruction *t;
    t = (instruction *)malloc(sizeof(instruction));
    t->opcode = mul_v;
    t->srcLine = q->line;
    make_operand(q->arg1, &t->arg1);
    make_numberoperand(&t->arg2, -1);

    make_operand(q->result, &t->result);
    q->taddress = nextinstrlabel();
    emit_instruction(t);
}