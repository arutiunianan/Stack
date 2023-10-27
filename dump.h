#ifndef DUMP_H_
#define DUMP_H_

#include "stack.h"

// #define _DEBUG

#ifdef _DEBUG

#define StackDump( stack ) STACKDUMP (( stack ), #stack, __FILE__, __LINE__, __func__  )

// StackDump_
void STACKDUMP( Stack* stack, const char* name, const char* file, int line, const char* func );
void PrintErrors( Stack* stack );

#endif

#endif // #define DUMP_H_