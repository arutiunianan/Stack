#include "stack.h"
#include "dump.h"

void RunTests( Stack* stack )
{
    assert( stack );
    StackPush( stack, 1 );
    //printf( "%d\n",stack->data[0] );
    StackPush( stack, 2 );
    StackPush( stack, 3 );
    StackPush( stack, 4 );
    StackPush( stack, 5 );

    printf( "(%d %d)\n",stack->capacity,stack->size );
    /*for(int i = 0; i < stack->size; i++)
    {
        printf("%d %d\n", stack->data[i], i);
    }
    // ( "" )*/
    int pop = 0;
    StackPop( stack, &pop );
    printf( "попнули %d\n", pop );
    StackPop( stack, &pop );
    printf("попнули %d\n", pop );
    //printf("(%d %d)\n", stack->capacity, stack->size);
    StackDump( stack );

}

int main( )
{
    Stack stack = {};
    StackCtor( &stack );

    RunTests( &stack );

	StackDtor( &stack );
    //printf("pooopppop");

}
