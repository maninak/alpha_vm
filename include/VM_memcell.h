#ifndef VM_MEMCELL_H
#define	VM_MEMCELL_H


#define AVM_STACKSIZE   4096
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))

typedef struct avm_memcell avm_memcell;
#include "VM_table.h"


typedef enum avm_memcell_t {
    number_m    =0,
    string_m    =1,
    bool_m      =2,
    table_m     =3,
    userfunc_m  =4,
    libfunc_m   =5,
    nil_m       =6,
    undef_m     =7
}avm_memcell_t;

struct avm_table;

struct avm_memcell {
    avm_memcell_t type;
    union {
        double          numVal;
        char *          strVal;
        unsigned char   boolVal;
        avm_table*      tableVal;
        unsigned        funcVal;
        char *          libfuncVal;
    } data;
};


typedef void (*memclear_func_t) (avm_memcell * m);
avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack (void);
extern void avm_memcellclear (avm_memcell *);
extern void memclear_string (avm_memcell * m);//TODO IMPLEMENT
extern void memclear_table (avm_memcell * m);//TODO IMPLEMENT

#endif	/* VM_MEMCELL_H */

