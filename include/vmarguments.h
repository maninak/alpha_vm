#ifndef VMARGUMENTS_H
#define	VMARGUMENTS_H

//#include <assert.h>
//#include "expressions.h"
//#include "quads.h"

/*
 * Enum values for the field type of vmargs
 */
typedef enum VMARG_TYPE {
	programfunc_a,          libfunc_a,              retval_a,	
	global_a,		local_a,                label_a,
	formal_a,		number_a,		bool_a,
	string_a,		nil_a,                  empty_a	
}VMARG_TYPE;
/*
 * Struct of vmarg
 */
typedef struct vmarg{

	VMARG_TYPE  type;   //Type of the argument
	unsigned    val;    //Value of the argument.In some occasion is the index of the arg in the proper Const_Table
}vmarg;
#endif