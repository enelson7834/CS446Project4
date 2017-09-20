/**<
Configuration file input nodes.

Nodes will store information from the configuration file and parse
the config file to retrieve necessary information.

@file ConfigFileInputNode.hh
@author Eugene Nelson
@data 9/18/17
@version 1.0 (Eugene Nelson 9/18/17)
*/
/////////////////////////////////////////////////////////////////////////////
// File Definitions
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
#include "LinkedList.hh"
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
    private:
        char aFilePath[ FILE_NAME_MAX_LENGTH ];
        char aLogOutputSpecification;
        char aLogFilePath[ LOG_FILE_NAME_MAX_LENGTH ];
        LinkedList<ConfigFileInputNode>* aListOfProcesses;

};

#endif