#ifndef CONST_TABLES_H
#define	CONST_TABLES_H

//#include "generator.h"
#include "instructions.h"
#include "vmarguments.h"


#define EXPAND_SIZE 1024
#define CURR_SIZE_STR 	(total_STR*sizeof(consts_newstring))
#define NEW_SIZE_STR	(EXPAND_SIZE*sizeof(consts_newstring)+CURR_SIZE_STR)

#define CURR_SIZE_NUM 	(total_NUM*sizeof(consts_newnumber))
#define NEW_SIZE_NUM	(EXPAND_SIZE*sizeof(consts_newnumber)+CURR_SIZE_NUM)


#define CURR_SIZE_LIB 	(total_LIB*sizeof(libfuncs_newused))
#define NEW_SIZE_LIB	(EXPAND_SIZE*sizeof(libfuncs_newused)+CURR_SIZE_LIB)

#define CURR_SIZE_USR 	(total_USR*sizeof(userfuncs_newfunc))
#define NEW_SIZE_USR	(EXPAND_SIZE*sizeof(userfuncs_newfunc)+CURR_SIZE_USR)


typedef struct consts_newstring{
    
    char* new_string;   //The value of string
}consts_newstring;

typedef struct consts_newnumber{
    
    double new_number;  //The value of number
}consts_newnumber;

typedef struct libfuncs_newused{
    
    char* libfunc_name; //The name of the library Function
}libfuncs_newused;

typedef struct userfuncs_newfunc{
    unsigned taddress;  //The number of the first produced final-Instruction
    unsigned locals;    //The number of locals
    char* name;         //The name of the user function
    
}userFunc;

/*
 * Adds a new string in the string table.
 * 
 * Returns the index of the imported string in the array (In the val field of the vmarg ussualy)
 */
unsigned    add_new_STR(char *);
/*
 * Expands the size of the table when it's full
 */
void        expand_STR();
/*
 * Adds a new number in the numbers table.
 * 
 * Returns the index of the imported number in the array (In the val field of the vmarg ussualy)
 */
unsigned    add_new_NUM(double);
/*
 * Expands the size of the table when it's full
 */
void        expand_NUM();
/*
 * Adds the lib function's name in the lib function table.
 * 
 * Returns the index of the imported "lib function"(just the name) in the array (In the val field of the vmarg ussualy)
 */
unsigned    add_new_LIB(char *);
/*
 * Expands the size of the table when it's full
 */
void        expand_LIB();
/*
 * Adds a user function(taddress,number of local arguments,name of the function)  in the user function table.
 * 
 * Returns the index of the imported "user function" in the array (In the val field of the vmarg ussualy)
 */
unsigned    add_new_USR(unsigned,unsigned,char *);
/*
 * Expands the size of the table when it's full
 */
void        expand_USR();
/*
 * Prints all the table's contents
 */
void		printConstTables();
#endif	/* CONST_TABLES_H */

