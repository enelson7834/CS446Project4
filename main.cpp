#include <iostream>
#include <cstring>
#include "ConfigFileInput.hh"
#include "MetaDataInfo.hh"

using namespace std;

int main( int argv, char* argc[ ] )
{
    ConfigFileInput ConfigFileTest( argc[ 1 ] );
    MetaDataInfo MetaDataFileTest( ConfigFileTest.GetFilePath( ) );

    MetaDataFileTest.ProcessData( ConfigFileTest );

	return 0;
}
