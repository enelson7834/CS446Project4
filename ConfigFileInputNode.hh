/**<
@file ConfigFileInputNode.hh
@author Eugene Nelson
@detailed   Will be used with the ConfigFileInput class to store the relevant
            tokens extracted from the file in the list of processes.
@version 	1.0 Eugene Nelson 
			Originally Developed ( 9 - 18 - 17 )
*/
/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives
/////////////////////////////////////////////////////////////////////////////
#ifndef namespace_config_file_input_node_hh
#define namespace_config_file_input_node_hh

/////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////
#define STR_MAX_LENGTH 300

/////////////////////////////////////////////////////////////////////////////
// Header Files
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstring>

/////////////////////////////////////////////////////////////////////////////
// Class Definitions
/////////////////////////////////////////////////////////////////////////////
class ConfigFileInputNode
{
	public:
	            ConfigFileInputNode( );
	            ConfigFileInputNode(    const char newProcessName[ ], 
	                                    const int newProcessValue );
                ConfigFileInputNode( const ConfigFileInputNode& copyNode );
	            ~ConfigFileInputNode( );
	    
	    char*   GetProcessName( );
	    int     GetProcessValue( );
	    
	    void    SetProcessName( char newProcessName[ ] );
	    void    SetProcessValue( int newProcessValue );
	                                    
	    bool    operator==( const char processName[ ] ) const; 
	    ConfigFileInputNode operator=( const ConfigFileInputNode& copyNode );
	    
	private:
	    char   aProcessName[ STR_MAX_LENGTH ];
	    int    aProcessValue;
};

#endif
