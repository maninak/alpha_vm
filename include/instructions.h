#ifndef _INSTRUCTIONS_H_
#define	_INSTRUCTIONS_H_

//#include <assert.h>
//#include <string.h>
#include "vmarguments.h"
//#include "quads.h"

#define EXPAND_SIZE_I   1024
#define CURR_SIZE_I 	(total_I*sizeof(instruction))
#define NEW_SIZE_I	(EXPAND_SIZE_I*sizeof(instruction)+CURR_SIZE_I)

typedef struct incomplete_jump{
    unsigned                    instrNo;        //The jump instruction number.
    unsigned                    iaddress;       //The i-code jump-target address
    struct incomplete_jump*     next;           //A trivial linked list.
}incomplete_jump;

extern incomplete_jump *       ij_head;     //Head to the incomplete_jumps trivial list
extern unsigned                ij_total;    //Counter that keeps how many ijs are in the list

//The enums for the VMOPCODE field of the instruction struct
typedef enum VMOPCODE { 
	assign_v,		add_v,                  sub_v,
        mul_v,			div_v,                  mod_v,
        uminus_v,               jeq_v,                  jne_v,
        jle_v,                  jge_v,                  jlt_v,        
        jgt_v,                    call_v, 		param_v,        
        ret_v, 			getretval_v, 		enterfunc_v,        
        exitfunc_v,		tablecreate_v,          tablegetelem_v,        
        tablesetelem_v,         jump_v,                 emptyquad_v,
        pusharg_v,		callfunc_v,             nop_v,                         
 	
}VMOPCODE;

typedef struct instruction {
	VMOPCODE     opcode;    //The opcode of the instruction
	vmarg       result;     //The result register
	vmarg	    arg1;       //The arg1 register
	vmarg	    arg2;       //The arg2 register
	unsigned    srcLine;    //The original input line
}instruction;


extern instruction * instructions;	// The data structure containing all the quads emitted
extern unsigned total_I;                // The maximum capacity of the array
extern unsigned currInstruction;        // The next empty slot in the array to input a quad

/**
 * Emits an instruction to the instructions Table
 */
void        emit_I (instruction);
/**
 * Expands the instructions Table when it's full
 */
void        expand_I ();
/**
 * Returns the current instruction number
 */
unsigned    nextinstructionlabel();

/**
 * Adds an incomplete jump in the ijs list
 */
void        add_incomplete_jump(unsigned,unsigned);

/**
 * Patches all the incomplete jumps in the list with the appropriate jump target
 */
void        patch_incomplete_jumps();
/**
 * Covnerts VMOPCODE to string value and returns it
 */
char *      VMOPtoString (VMOPCODE);
/**
 * Covnerts VMARG_TYPE to string value and returns it
 */
char *      VMATtoString (VMARG_TYPE);
/**
 * Prints the instructions Table
 */
void        printInstructions();

#endif	/* INSTRUCTIONS_H */
