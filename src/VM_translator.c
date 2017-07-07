#ifndef _VM_TRANSLATOR_C_
#define _VM_TRANSLATOR_C_

#include "../include/VM_translator.h"




avm_memcell * avm_translate_operand (vmarg * arg, avm_memcell * reg){
    
    switch (arg->type){
        
        /*Variables*/
        case global_a:
            return &stack[AVM_STACKSIZE-1-arg->val];
        case local_a:
            return &stack[topsp-arg->val];
        case formal_a:
            return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a:
            return &retVal;
        case number_a:
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        case string_a:
            reg->type = string_m;
            reg->data.strVal = consts_getstring(arg->val);
            return reg;
        case bool_a:
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        case nil_a:
            reg->type = nil_m;
            return reg;
        case programfunc_a:
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val; //TODO edw prepei na fortwnw thn timh apo ton pinaka giati den exw thn timh sto val
            return reg;
        case libfunc_a:
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        default:
            assert(0);       
    }
}

#endif