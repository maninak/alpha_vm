#ifndef TRANSLATOR_H
#define	TRANSLATOR_H

#include <assert.h>
#include "vmarguments.h"
#include "VM_memcell.h"
#include "VM_execute.h"

#define AVM_STACKENV_SIZE 4

extern avm_memcell ax, bx, cx;
extern avm_memcell retVal;
extern unsigned top,topsp;

double  consts_getnumber (unsigned index);//TODO IMPLEMENT
char *  consts_getstring (unsigned index);//TODO IMPLEMENT
char *  libfuncs_getused (unsigned index);//TODO IMPLEMENT
//Prepei na ftiaksw kai mia gia ta userFuncs epeidh den pernaw thn dieuthynsh
//sto val alla thn thesh tou pinaka pou einai apothikeumenh h user function

avm_memcell * avm_translate_operand (vmarg * arg, avm_memcell * reg);

#endif	/* TRANSLATOR_H */

