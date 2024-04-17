#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "quads.h"



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

void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line){
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