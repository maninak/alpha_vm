#ifndef _VM_TABLES_C_
#define _VM_TABLES_C_

#include "../include/VM_execute.h"
#include "../include/VM_translator.h"



void execute_newtable (instruction * instr) {
    avm_memcell * lv = avm_translate_operand(&instr->result, (avm_memcell *) 0);
    assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retVal));
    
    avm_memcellclear(lv);
    
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}


void execute_tablegetelem (instruction * instr){
    
    avm_memcell * lv = avm_translate_operand(&instr->result, (avm_memcell *) 0);
    avm_memcell * t = avm_translate_operand(&instr->arg1, (avm_memcell *) 0);
    avm_memcell * i = avm_translate_operand(&instr->arg2, &ax);
    
    assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retVal));
    assert(t && &stack[0] <= t && &stack[top] > t);
    assert(i);
    
    avm_memcellclear(lv);
    lv->type = nil_m;   /* Default value. */
    
    if(t->type != table_m){
        avm_error("illegal use of lvalue as table!",currLine);
    }
    else{
        avm_memcell * content = avm_tablegetelem(t->data.tableVal, i);
        if (content){
            avm_assign(lv, content);
        }
        else{
            char * ts = avm_tostring(t);
            char * is = avm_tostring(i);
            
            avm_warning("Table item not found!",currLine);
            free(ts);
            free(is);
        }   
    }
}

void execute_tablesetelem (instruction * instr){
    
    avm_memcell * t = avm_translate_operand(&instr->result, (avm_memcell *) 0);
    avm_memcell * i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell * c = avm_translate_operand(&instr->arg2, &bx);
    
    assert(t && &stack[0] <= t && &stack[top] > t);
    assert(i && c);
    
    if(t->type != table_m){
        avm_error("illegal use of lvalue as table!",currLine);
    }
    else{
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}





#endif