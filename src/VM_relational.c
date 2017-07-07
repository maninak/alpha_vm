#ifndef _VM_RELATIONAL_C_
#define _VM_RELATIONAL_C_

#include "../include/VM_execute.h"
#include "../include/VM_translator.h"






equality_func_t equalityFuncs[] = {
    equality_numbers,
    equality_strings,
    equality_bools,
    equality_tables,
    equality_userfuncs,
    equality_libfuncs,
    equality_nil,
    equality_undef
};


unsigned char equality_numbers(avm_memcell * m1,avm_memcell * m2 ){
    assert(m1->type == number_m && m2->type == number_m);
    return (m1->data.numVal == m2->data.numVal);
}

unsigned char equality_strings(avm_memcell * m1,avm_memcell * m2 ){
    assert(m1->type == string_m && m2->type == string_m);
    return (strcmp(m1->data.strVal,m2->data.strVal) == 0);
}

unsigned char equality_bools(avm_memcell * m1,avm_memcell * m2 ){
    assert(m1->type == bool_m && m2->type == bool_m);
    return (m1->data.boolVal == m2->data.boolVal);
}

unsigned char equality_tables(avm_memcell * m1,avm_memcell * m2 ){
    
}

unsigned char equality_userfuncs(avm_memcell * m1,avm_memcell * m2 ){
    
}

unsigned char equality_libfuncs(avm_memcell * m1,avm_memcell * m2 ){
    
}

unsigned char equality_nil(avm_memcell * m1,avm_memcell * m2 ){
    assert(0);
    return 0;
}

unsigned char equality_undef(avm_memcell * m1,avm_memcell * m2 ){
    assert(0);
    return 0;
}


void execute_jeq (instruction * instr){
    assert(instr->result.type == label_a);
    
    avm_memcell * rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell * rv2 = avm_translate_operand(&instr->arg2, &bx);
    
    unsigned char result = 0;
    
    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality!",currLine);
        //TODO Na valw thn entolh executionFinished = 1 mesa sthn avm_error
    }
    else if(rv1->type == nil_m || rv2->type == nil_m){
        result = (rv1->type == nil_m) && (rv2->type == nil_m);
    }
    else if(rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if(rv1->type != rv2->type){
        avm_error("Equality check is illegal!",currLine);
    }
    else{
        /*TODO Equality check with dispatching*/
        result = (*equalityFuncs[rv1->type])(rv1,rv2);
    }

    if(!(executionFinished) && result){//TODO des shmeiwsh sthn dialeksh sel.29 lecture 15
        pc = instr->result.val;
    }
}

void execute_jnq (instruction * instr){
    assert(instr->result.type == label_a);
    
    avm_memcell * rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell * rv2 = avm_translate_operand(&instr->arg2, &bx);
    
    unsigned char result = 0;
    
    if(rv1->type == undef_m || rv2->type == undef_m){
        avm_error("'undef' involved in equality!",currLine);
        //TODO Na valw thn entolh executionFinished = 1 mesa sthn avm_error
    }
    else if(rv1->type == nil_m || rv2->type == nil_m){
        result = (rv1->type == nil_m) && (rv2->type == nil_m);
    }
    else if(rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if(rv1->type != rv2->type){
        avm_error("Unequal check is illegal!",currLine);
    }
    else{
        /*TODO Equality check with dispatching*/
        result = (*equalityFuncs[rv1->type])(rv1,rv2);
    }

    if(!(executionFinished) && result){//TODO des shmeiwsh sthn dialeksh sel.29 lecture 15
        pc = instr->result.val;
    }
}






#endif