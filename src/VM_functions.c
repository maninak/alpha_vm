#ifndef _VM_FUNCTIONS_C_
#define _VM_FUNCTIONS_C_

#include "../include/VM_execute.h"
#include "../include/VM_translator.h"
#include "../include/const_tables.h"


unsigned totalActuals = 0;



unsigned avm_totalactuals (void){

    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}
avm_memcell * avm_getactual (unsigned i){
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

userFunc * avm_getfuncinfo(unsigned address){}//TODO IMPLEMENT



void avm_dec_top (void) {
    if(!top){   /*stack overflow*/
        avm_error("stack overflow",currLine);
        executionFinished = 1;
    }
    else
        --top;
}

void avm_push_envvalue (unsigned val){
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}

void avm_calllibfunc (char * id){
    library_func_t f = avm_getlibraryfunc(id);
    
    if(!f){
        avm_error("unsupported lib func! ",currLine);
        executionFinished = 1;
    }
    else{
        /* Notice that enter function and exit function are called manually! */
        topsp = top;    /* Enter function sequence. No stack locals. */
        totalActuals = 0;
        (*f)();         /* Call library function. */
        if(!executionFinished)  /* An error may naturally occur inside. */
            execute_funcexit((instruction *) 0);/* Return sequence. */
    }
}

void avm_callsaveenvironment (void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals +2);
    avm_push_envvalue(topsp);
}

unsigned avm_get_envvalue (unsigned i){
    assert(stack[i].type = number_m);
    
    unsigned val = (unsigned) stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double) val));
    
    return val;
}











/*
 * EXECUTIONS
 *
 */

void execute_call (instruction * instr){
    
    avm_memcell * func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();
    
    switch (func->type) {
        
        case userfunc_m:
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
            
        case string_m:
            avm_calllibfunc(func->data.strVal);
            break;
            
        case libfunc_m:
            avm_calllibfunc(func->data.libfuncVal);
            break;
        default:
            char * s = avm_tostring(func);
            avm_error("call: cannot bind functionId to function!",currLine);
            free(s);
            executionFinished = 1;
    }
}

void execute_pusharg (instruction * instr){
    avm_memcell * arg = avm_translate_operand(&instr->arg1, &ax);
    assert(arg);
    /*This is actually stack[top] = arg, but we have to use avm_assign.*/
    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter (instruction * instr){
    avm_memcell * func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);/* Func address should match PC. */
    
    /*Callee actions here. */
    totalActuals = 0;
    userFunc * funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->locals;
    
}

void execute_funcexit (instruction * unused){
    
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while (oldTop++ <= top) /*Intentionally ignoring first*/
        avm_memcellclear(&stack[oldTop]);
}


/**
 * LIB FUNCS
 * 
 */

void libfunc_totalarguments (void){
    
    /**
     * Get topsp of previous activation records
     */
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retVal);
    
    if(!p_topsp){   /* If 0, no previous activation record. */
        avm_error("'totalarguments' called outside a function! ",currLIne);
        retVal.type = nil_m;
    }
    else{
        /**
         * Extract the number of actual arguments for the previous activation record.
         */
        
        retVal.type = number_m;
        retVal.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);   
    }
}

//PRINT
/* Implementation of the library function 'print'.
 * It displays every argument at the console.
 */
void libfunc_print (void){
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i){
        char * s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

//TO_STRING
tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};
/* Implementation of the library function 'toString'.
 * Returns any  cell to string.
 */
char * avm_tostring(avm_memcell * m){
    assert(m->type >= 0 && m->type < undef_m);
    return (*tostringFuncs[m->type])(m);
}

//TO_BOOL
unsigned char number_tobool (avm_memcell * m){
    return m->data.numVal != 0;
}
unsigned char string_tobool (avm_memcell * m){
    return m->data.strVal[0] != 0;
}
unsigned char bool_tobool (avm_memcell * m){
    return m->data.boolVal;
}
unsigned char table_tobool (avm_memcell * m){
    return 1;
}
unsigned char userfunc_tobool (avm_memcell * m){
    return 1;
}
unsigned char lib_tobool (avm_memcell * m){
    return 1;
}
unsigned char nil_tobool (avm_memcell * m){
    return 0;
}
unsigned char undef_tobool (avm_memcell * m){
    assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool (avm_memcell * m){
    assert(m->type >= 0 && m->type < undef_m);
    return (* toboolFuncs[m->type])(m);
}

//TYPE_OF
void libfunc_typeof (void){
    
    unsigned n = avm_totalactuals();
    
    if(n != 1){
        avm_error("one argument expected in 'typeof'! ",currLine);
    }
    else{
        /** That's how a library function returns a result. 
         *  It has to only set the 'retval' register!
         */
        avm_memcellclear(&retVal);  /* Don't forget to clean-it up! */
        retVal.type = string_m;
        retVal.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}


#endif