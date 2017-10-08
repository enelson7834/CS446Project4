#ifndef MEM_FUNC_C
#define MEM_FUNC_C

#include <time.h>
#include <stdlib>

#include "MemoryFunction.hh"

unisgned int allocateMemory( int totMem )
{
	unsigned int address,

	srand( time( NULL ) );

	if( totMem > 0 )
	{
		address = rand() % totMem;
	}

	return address;
}

#endif