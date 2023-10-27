#include "dump.h"

void STACKDUMP( Stack* stack, const char* name, const char* file, int line, const char* func )
{

    if( !stack )
    {
        printf( "Stack is not exist\n" );
        return;
    }
    
    printf( "Stack [%p], \"%s\" from FUNC: %s(%zu)\nFILE: %s\n", stack, name, func, line, file );

    PrintErrors( stack );

    printf( "capacity = %d\n", stack->capacity );
    printf( "size = %d\n", stack->size );
    for( int i = 0; i < stack->capacity; i++ )
    {

        printf( "%d, ", stack->data[i] );

    }


}

void PrintErrors( Stack* stack )
{

    if ( !stack->errors )
        printf("\nNO ERRORS\n");
    else
    {
        if ( stack->errors & stackError )           
            printf( "Stack is not exist\n" );
        if ( stack->errors & dataError )           
            printf( "Data is not exist\n" );
        if ( stack->errors & stackLeftCanaryError )         
            printf( "Stack left canary is damaged\n" );
        if ( stack->errors & stackRightCanaryError )      
            printf( "Stack right canary is damaged\n" );
        if ( stack->errors & dataLeftCanaryError )             
            printf( "Data left canary is damaged\n" );
        if ( stack->errors & dataRightCanaryError )      
            printf( "Data right canary is damaged\n" );
        if ( stack->errors & hashError )         
            printf( "Hash is damaged\n" );
        if ( stack->errors & sizeError )         
            printf( "Size of data is negative number\n" );
        if ( stack->errors & capacityError )              
            printf( "Capasity of data is negative number\n" );
    }

}