#ifndef _VM_TABLE_C_
#define _VM_TABLE_C_

#include "../include/VM_table.h"
#include <assert.h>


avm_table * avm_tablenew (void){
    avm_table * t = (avm_table *)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);
    
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    
    return t;
}

void avm_tabledestroy (avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}

void avm_tableincrefcounter (avm_table * t){
    ++(t->refCounter);
}

void avm_tabledecrefcounter (avm_table * t){
    assert(t->refCounter>0);
    if(!(--(t->refCounter))){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit (avm_table_bucket ** p){
    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i){
        p[i] = (avm_table_bucket *) 0;
    }
}

void    avm_tablebucketsdestroy (avm_table_bucket ** p){
    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i){
        for(avm_table_bucket * b = * p; b;){
            avm_table_bucket * del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *) 0;
    }
}
#endif