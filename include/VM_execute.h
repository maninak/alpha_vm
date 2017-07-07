#ifndef VM_EXECUTE_H
#define	VM_EXECUTE_H

#include <stdio.h>
#include <assert.h>
#include "VM_memcell.h"
#include "const_tables.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

extern unsigned char    executionFinished;
extern unsigned         pc;
extern unsigned         currLine;
extern unsigned         codeSize;

#define AVM_ENDING_PC   codeSize

/*VM_execute.c*/
typedef void (*execute_func_t)  (instruction*);

extern void execute_cycle       (void);
extern void avm_warning         (char * message,unsigned line);
extern void avm_error           (char * message,unsigned line);
extern void avm_initialize      (void);

/*VM_assign.c*/
extern void avm_assign (avm_memcell* lv,avm_memcell* rv);

/*VM_functions.c*/
#define AVM_NUMACTUALS_OFFSET   +4
#define AVM_SAVEDPC_OFFSET      +3
#define AVM_SAVEDTOP_OFFSET     +2
#define AVM_SAVEDTOPSP_OFFSET   +1

typedef void        (*library_func_t)       (void);

library_func_t      avm_getlibraryfunc      (char * id);//TODO IMPLEMENT /*Typical hashing.*/
extern unsigned     avm_totalactuals        (void);
extern avm_memcell* avm_getactual           (unsigned i);
extern userFunc *   avm_getfuncinfo         (unsigned address);//TODO IMPLEMENT
extern void         avm_dec_top             (void);
extern void         avm_push_envvalue       (unsigned val);
extern char *       avm_tostring            (avm_memcell *); /* Caller frees. */
extern void         avm_calllibfunc         (char * funcName);
extern void         avm_callsaveenvironment (void);
extern unsigned     avm_get_envvalue        (unsigned i);

/*VM_arithmetic.c*/
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef double (*arithmetic_func_t)(double x, double y);

extern double add_impl (double x, double y);
extern double sub_impl (double x, double y);
extern double mul_impl (double x, double y);
extern double div_impl (double x, double y);
extern double mod_impl (double x, double y);

extern void execute_arithmetic (instruction * instr);

/*VM_relational.c*/
char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};
typedef unsigned char (*equality_func_t)(avm_memcell * m1,avm_memcell * m2);

extern unsigned char equality_numbers   (avm_memcell * m1,avm_memcell * m2 );
extern unsigned char equality_strings   (avm_memcell * m1,avm_memcell * m2 );
extern unsigned char equality_bools     (avm_memcell * m1,avm_memcell * m2 );
extern unsigned char equality_tables    (avm_memcell * m1,avm_memcell * m2 );   //TODO IMPLEMENT
extern unsigned char equality_userfuncs (avm_memcell * m1,avm_memcell * m2 );   //TODO IMPLEMENT
extern unsigned char equality_libfuncs  (avm_memcell * m1,avm_memcell * m2 );   //TODO IMPLEMENT
extern unsigned char equality_nil       (avm_memcell * m1,avm_memcell * m2 );
extern unsigned char equality_undef     (avm_memcell * m1,avm_memcell * m2 );


///*VM_tables.c*/
//avm_memcell *   avm_tablegetelem(avm_table * table, avm_memcell * index);//TODO IMPLEMENT
//void            avm_tablesetelem(avm_table * table, avm_memcell * index, avm_memcell * content);//TODO IMPLEMENT


//Executions
extern void execute_assign          (instruction*);
extern void execute_add             (instruction*);
extern void execute_sub             (instruction*);
extern void execute_mul             (instruction*);
extern void execute_div             (instruction*);
extern void execute_mod             (instruction*);
extern void execute_uminus          (instruction*);//TODO IMPLEMENTED WITH MUL SO DONT IMPLEMENT
extern void execute_jeq             (instruction*);
extern void execute_jne             (instruction*);
extern void execute_jle             (instruction*);//TODO IMPLEMENT
extern void execute_jge             (instruction*);//TODO IMPLEMENT
extern void execute_jlt             (instruction*);//TODO IMPLEMENT
extern void execute_jgt             (instruction*);//TODO IMPLEMENT
extern void execute_call            (instruction*);
extern void execute_pusharg         (instruction*);
extern void execute_funcenter       (instruction*);
extern void execute_funcexit        (instruction*);
extern void execute_newtable        (instruction*);
extern void execute_tablegetelem    (instruction*);
extern void execute_tablesetelem    (instruction*);
extern void execute_nop             (instruction*);//TODO IMPLEMENT

/*Lib Funcs*/
extern void libfunc_totalarguments (void);
extern void avm_registerlibfunc (char *id, library_func_t addr);//TODO IMPLEMENT
//print
extern void libfunc_print (void);
//toString
typedef char * (*tostring_func_t)(avm_memcell *);

extern char * number_tostring   (avm_memcell *);
extern char * string_tostring   (avm_memcell *);
extern char * bool_tostring     (avm_memcell *);
extern char * table_tostring    (avm_memcell *);
extern char * userfunc_tostring (avm_memcell *);
extern char * libfunc_tostring  (avm_memcell *);
extern char * nil_tostring      (avm_memcell *);
extern char * undef_tostring    (avm_memcell *);

//toBool
typedef unsigned char (*tobool_func_t)(avm_memcell *);

extern unsigned char number_tobool      (avm_memcell * m);
extern unsigned char string_tobool      (avm_memcell * m);
extern unsigned char bool_tobool        (avm_memcell * m);
extern unsigned char table_tobool       (avm_memcell * m);
extern unsigned char userfunc_tobool    (avm_memcell * m);
extern unsigned char lib_tobool         (avm_memcell * m);
extern unsigned char nil_tobool         (avm_memcell * m);
extern unsigned char undef_tobool       (avm_memcell * m);

extern unsigned char avm_tobool         (avm_memcell * m);

//typeOf
extern void libfunc_typeof (void);

#endif	/* VM_EXECUTE_H */

