#ifndef _VM_MEMCELL_C_
#define _VM_MEMCELL_C_

#include "../include/VM_memcell.h"

memclear_func_t memclearFuncs[] = {
    0,  /* number */
    memclear_string,
    0,  /*bool*/
    memclear_table,
    0,  /*userfunc*/
    0,  /*libfunc*/
    0,  /*nil*/
    0   /*undef*/
};
static void avm_initstack (void){
    
    for(unsigned i=0; i<AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_memcellclear (avm_memcell * m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f)
            (*f)(m);
        m->type = undef_m;
    }
}

#endif