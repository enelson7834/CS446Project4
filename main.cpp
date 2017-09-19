#include <iostream>
#include "ConfigFileInput.hh"

using namespace std;

int main( int argv, char* argc[ ] )
{
	ConfigFileInput test1( argc[ 1 ] );

	cout << test1.GetProcessValue( "memory" ) << endl;

	return 0;
}