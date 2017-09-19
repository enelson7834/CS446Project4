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
	    
	private:
	    char   aProcessName[ STR_MAX_LENGTH ];
	    int    aProcessValue;
};

#endif
