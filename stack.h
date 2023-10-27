#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
//#include "dump.h"


typedef int Elem;

#define _DEBUG

const int constCapsity = 2;

#ifdef _DEBUG

#define StackCtor( stack ) STACKCTOR(( stack ), #stack, __FILE__, __LINE__, __func__ )

typedef enum CanaryConstants
{ 
    canaryStack = 0xB0BA2410, 
    canaryData = 0xB1BA2003 
    
} CanaryConstants;

typedef enum Errors
{    
    stackError            = 1 << 0,
    dataError             = 1 << 1,
    stackLeftCanaryError  = 1 << 2,
    stackRightCanaryError = 1 << 3,
    dataLeftCanaryError   = 1 << 4,
    dataRightCanaryError  = 1 << 5,
    hashError             = 1 << 6,
    sizeError             = 1 << 7,
    capacityError         = 1 << 8
    
} Errors;

typedef struct Stack
{ 
    long leftCanary;

    Elem* data; 

    int capacity; 
    int size;
    int hash;
    int errors;

    int         line;
	const char* file;
	const char* func;
	const char* name;

    long rightCanary;

} Stack;

int STACKCTOR( Stack* stack, const char* name, const char* file, int line, const char* func );
int StackDtor( Stack* stack );


#else

typedef struct Stack
{ 
    Elem* data; 
    int capacity; 
    int size;

} Stack;

void StackCtor( Stack* stack );
void StackDtor( Stack* stack );

#endif

int StackPush( Stack* stack, int val );
int StackPop( Stack* stack, int* popvalue );


#endif // #define STACK_H_