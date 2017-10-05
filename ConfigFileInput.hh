/**<
@file ConfigFileInputNode.hh
@author Eugene Nelson
@breif  The header file for the ConfigFileInputNode class
@version    1.0 Eugene Nelson 
            Originally Developed ( 9 - 18 - 17 )
*/
/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives
/////////////////////////////////////////////////////////////////////////////
#ifndef namespace_config_file_input_hh
#define namespace_config_file_input_hh

/////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////
#define FILE_NAME_MAX_LENGTH 30
#define STR_MAX_LENGTH 300
#define LOG_FILE_NAME_MAX_LENGTH 30

/////////////////////////////////////////////////////////////////////////////
// Header Files
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <list>
#include "ConfigFileInputNode.hh"

/////////////////////////////////////////////////////////////////////////////
// Namespace Declaration
/////////////////////////////////////////////////////////////////////////////
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Class Definitions
/////////////////////////////////////////////////////////////////////////////
class ConfigFileInput
{
    public:
        ConfigFileInput( char* fileName );
        ConfigFileInput( const ConfigFileInput& copyInput );
        ~ConfigFileInput( );

        int GetNumberOfProcesses( );
        int GetProcessValue( const char processName[ ] );
        char* GetProcessName( const int position );

        char GetLogOutputSpecification( );
        char* GetFilePath( );
        char* GetLogFilePath( );
    protected:
        bool ParseLine( char lineToParse[ ] );
        void RemoveSpaces( char lineToRemoveSpaces[ ] );
        void AdjustLineElements( char lineToAdjust[ ], int positionToAdjust );
    private:
        char aFilePath[ FILE_NAME_MAX_LENGTH ];
        char aLogOutputSpecification;
        char aLogFilePath[ LOG_FILE_NAME_MAX_LENGTH ];
        list<ConfigFileInputNode> aListOfProcesses;

};

#endif
