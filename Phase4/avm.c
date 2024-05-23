#include "avm.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter>0);
    if(!--t->refCounter)
        avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket** p){
    unsigned i;
    for(i=0;i<AVM_TABLE_HASHSIZE;++i)
        p[i]= (avm_table_bucket*) 0;
}

avm_table* avm_tablenew(void){
    avm_table* t=(avm_table*)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    t->refCounter=t->total=0;
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

//copilot did it
void avm_memcellclear(avm_memcell* m){
    if(m->type!=undef_m){
        m->type=undef_m;
        memset(&(m->data),0,sizeof(m->data));
    }
}

void avm_tablebucketdestroy(avm_table_bucket** p){
    for(unsigned i=0;i<AVM_TABLE_HASHSIZE;++i, ++p){
        for(avm_table_bucket* b=*p; b;){
            avm_table_bucket* del=b;
            b=b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}

void avm_tabledestroy(avm_table* t){
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

avm_memcell* avm_translate_operand(vmarg* arg,avm_memcell* reg){
    switch(arg->type){
        case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a: return &stack[topsp-arg->val];
        case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a: return &retval;
        case number_a:{
            reg->type=number_m;
            reg->data.numVal=consts_getnumber(arg->val);
            return reg;
        }
        case string_a:{
            reg->type=string_m;
            reg->data.strVal=strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a:{
            reg->type=bool_m;
            reg->data.boolVal=arg->val;
            return reg;
        }
        case nil_a: reg->type=nil_m; return reg;
        case userfunc_a:{
            reg->type=userfunc_m;
            reg->data.funcVal=arg->val; // h ayto h apo kato
            reg->data.funcVal=userfuncs_get(arg->val)->address;
            return reg;
        }
        case libfunc_a:{
            reg->type=libfunc_m;
            reg->data.libfuncVal=libfuncs_getused(arg->val);
            return reg;
        }
        default: assert(0);
    }
}

void execute_cycle(void){
    if(executionFinished){
        return;
    }else if(pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    }else{
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if(instr->srcLine){
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC){
            ++pc;
        }
    }
}