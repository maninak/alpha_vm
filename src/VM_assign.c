#ifndef _VM_ASSIGN_C_
#define _VM_ASSIGN_C_

#include "../include/VM_execute.h"
#include "../include/VM_translator.h"




void avm_assign (avm_memcell * lv,avm_memcell * rv){
    
    if (lv==rv){     /*Same cells? Destructive to assign!*/
        return;
    }
    if(lv->type == table_m &&   /*Same tables? no need to assign.*/
       rv->type == table_m &&
       lv->data.tableVal == rv->data.tableVal){
        return;
    }
    if(rv->type == undef_m){    /*From undefined r-value? warning!!*/
        avm_warning("assigning from 'undef' content!",currLine);
    }
    
    avm_memcellclear(lv);   /*Clear old cell contents*/
    
    memcpy(lv, rv, sizeof(avm_memcell));
    
    /*Now take care of copied values or reference counting*/
    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if(lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
    
    
}


void execute_assign (instruction* instr){
    avm_memcell * lv = avm_translate_operand(&instr->result, (avm_memcell *) 0);
    avm_memcell * rv = avm_translate_operand(&instr->arg1, &ax);
    
    assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv==&retval));
    assert(rv);
    
    avm_assign(lv,rv);
}

#endif