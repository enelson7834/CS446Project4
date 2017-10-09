#include "MemoryFunction.hh"

unsigned int allocateMemory( int totMem )
{
	unsigned int address;

	srand( time( NULL ) );

	if( totMem > 0 )
	{
		address = rand() % totMem;
	}

	return address;
}