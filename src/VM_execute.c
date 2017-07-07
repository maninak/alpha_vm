#ifndef _VM_EXECUTE_C_
#define _VM_EXECUTE_C_

#include "../include/VM_execute.h"

unsigned char    executionFinished = 0;
unsigned         pc = 0;
unsigned         currLine = 0;
unsigned         codeSize = 0;

instruction * code = (instruction *) 0;

void execute_cycle (void){
    
    if(executionFinished)
        return;
    else if( pc ==  AVM_ENDING_PC){
        executionFinished = 1;
        return ;
    }
    else{
        assert (pc<AVM_ENDING_PC);
        instruction* instr = code +pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        
        if(instr->srcLine)
            currLine = instr->srcLine;
        unsigned oldPC =pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC)
            ++pc;
    }
}

void avm_warning (char * message,unsigned line){
    printf("WARNING:%s\nAt Line:%u\n",message,line);
}
void avm_error (char *,unsigned){
    printf("ERROR:%s\nAt Line:%u\n",message,line);
    executionFinished=1;
}




execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,       
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

void avm_initialize (void){
    
    avm_initstack();
    
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);

    /**
     * Same for all the rest library functions.
     */
}

#endif