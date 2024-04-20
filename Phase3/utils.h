
#include "quads.h"
void check_arith(expr *e, const char *context);
expr *lvalue_expr(symbol *sym);
expr *newexpr(expr_t t);
char *newtempname();
void resettemp();
SymbolTableEntry *newtemp();
