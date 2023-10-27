#include "stack.h"
#include "dump.h"

#ifdef _DEBUG

int StackState( Stack* stack ) 
{
	if ( stack == NULL )
    {
        stack->errors |= stackError;
        return 1;
    }

    if ( stack->data == NULL )
    {
        stack->errors |= dataError;
        return 1;
    }

	if ( stack->leftCanary != canaryStack )
	{
        stack->errors |= stackLeftCanaryError;
        return 1;
    }

	if ( stack->rightCanary != canaryStack )
	{
        stack->errors |= stackRightCanaryError;
        return 1;
    }

    if ( stack->data[-1] != canaryData )
    {
        stack->errors |= dataLeftCanaryError;
        return 1;
    }

    if ( stack->data[stack->size] != canaryData )
    {
        stack->errors |= dataRightCanaryError;
        return 1;
    }

    int hash = Hash( stack, sizeof(Stack) ) + Hash( stack->data, sizeof(Elem) * stack->size );

    if ( stack->hash != hash )
    {
        stack->errors |= hashError;
        return 1;
    }

    if ( stack->size < 0 )
    {
        stack->errors |= sizeError;
        return 1;
    }

    if ( stack->capacity < 0 )
    {
        stack->errors |= capacityError;
        return 1;
    }
    return 0;

}

int STACKCTOR( Stack* stack, const char* name, const char* file, int line, const char* func )
{
    if (!stack)
	{
		StackDump(stack);
		return 1;
	}

    stack->line = line;
    stack->name = name;
    stack->file = file;
    stack->func = func;

    stack->leftCanary = canaryStack;
    stack->rightCanary = canaryStack;
    stack->hash = Hash( stack, sizeof(Stack) ) + Hash( stack->data, sizeof(Elem) * stack->size );

    stack->size = 0;
    stack->capacity = constCapsity;

    stack->data = ( Elem* ) calloc ( stack->capacity + 2, sizeof(Elem) );

    stack->data = stack->data + sizeof(int);
    stack->data[-1] = canaryData;
    stack->data[stack->capacity] = canaryData;

    stack->hash = Hash( stack, sizeof(Stack) ) + Hash( stack->data, sizeof(Elem) * stack->size );
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    return 0;

}

int StackDtor( Stack* stack )
{
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    stack->line = -1;
    stack->name = "";
    stack->file = "";
    stack->func = "";

    stack->leftCanary = -1;
    stack->rightCanary = -1;

    stack->size = -1;
    stack->capacity = -1;


    free( stack->data );
    stack->data = NULL;

}

int StackPush( Stack* stack, int val )
{
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    if( stack->capacity <= stack->size )
    {
        stack->capacity = stack->capacity * 2;

        // StackRealloc
        stack->data = stack->data - sizeof(int);
        stack->data = ( Elem* ) realloc ( stack->data, sizeof(Elem) * ( stack->capacity + 2 ) );
        stack->data = stack->data + sizeof(int);

        stack->data[-1] = canaryData;
        stack->data[stack->capacity] = canaryData;

    }

    stack->hash = Hash( stack, sizeof(Stack) ) + Hash( stack->data, sizeof(Elem) * stack->size );
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    stack->data[stack->size++] = val;

    return 0;

}

int StackPop( Stack* stack, int* popvalue )
{
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    *popvalue = stack->data[stack->size - 1];

    if( stack->capacity / 4 >= stack->size )
    {
        stack->capacity = stack->capacity / 2;
        
        stack->data = stack->data - sizeof(int);
        stack->data = ( Elem* ) realloc ( stack->data, sizeof(Elem) * ( stack->capacity + 2 ) );
        stack->data = stack->data + sizeof(int);

        stack->data[-1] = canaryData;
        stack->data[stack->capacity] = canaryData;

    }

    stack->hash = Hash( stack, sizeof(Stack) ) + Hash( stack->data, sizeof(Elem) * stack->size );
    if( StackState( stack ) ) return 1;
    StackDump( stack );

    stack->size--;
    //return popVal;
    return 0;

}


#else

// typedef double Elem_t;
// stackCtor( Stack* self, int capacity )
void StackCtor( Stack* stack )
{
    assert( stack );

    // Capacity
    stack->capacity = constCapsity;
    stack->size = 0;
    stack->data = ( Elem* ) calloc ( stack->capacity, sizeof(Elem) );

}

void StackDtor( Stack* stack )
{   
    assert( stack );

    free( stack->data );
    stack->data = NULL;
    stack->capacity = -1;
    stack->size = -1;

}

void StackPush( Stack* stack, int val )
{
    assert( stack );

    if( size stack->size >= stack->capacity )
    {
        stack->capacity = stack->capacity * 2;
        stack->data = ( Elem* ) realloc ( stack->data, sizeof(Elem) * stack->capacity );

    }

    stack->data[stack->size++] = val;

}

// different signature
int StackPop( Stack* stack )
{
    assert( stack );
    // pop_val
    int pop_val = stack->data[stack->size - 1];

    if( stack->capacity / 4 >= stack->size )
    {
        stack->capacity = stack->capacity / 2;
        stack->data = ( Elem* ) realloc ( stack->data, sizeof(Elem) * stack->capacity );

    }

    stack->size--;
    return pop_val;

}
#endif