/**
@file ConfigFileInputNode.cc
@author Eugene Nelson
@breif The implamentation for the ConfigFileInputNode class
@version    1.0 Eugene Nelon
            Originally developed ( 9 - 20 - 17 ) 
*/
#include "ConfigFileInputNode.hh"

ConfigFileInputNode::ConfigFileInputNode( )
{
    strcpy( aProcessName, "None" );
    aProcessValue = -1;
}

ConfigFileInputNode::ConfigFileInputNode(   const char newProcessName[ ],
                                            const int newProcessValue )
{
    strcpy( aProcessName, newProcessName );
    aProcessValue = newProcessValue;
}

ConfigFileInputNode::ConfigFileInputNode( const ConfigFileInputNode& copyNode )
{
    strcpy( aProcessName, copyNode.aProcessName );
    aProcessValue = copyNode.aProcessValue;
}


ConfigFileInputNode::~ConfigFileInputNode( )
{
    strcpy( aProcessName, "None" );
    aProcessValue = -1;
}

char*   ConfigFileInputNode::GetProcessName( )
{
    return aProcessName;
}

int     ConfigFileInputNode::GetProcessValue( )
{
    return aProcessValue;
}

void    ConfigFileInputNode::SetProcessName( char newProcessName[ ] )
{
    strcpy( aProcessName, newProcessName );
}
void    ConfigFileInputNode::SetProcessValue( int newaProcessValue )
{
    aProcessValue = newaProcessValue;
}
                                
bool    ConfigFileInputNode::operator==( const char processName[ ] ) const
{
    return strcmp( aProcessName, processName );
}
ConfigFileInputNode ConfigFileInputNode::operator=( 
                                    const ConfigFileInputNode& copyNode )
{
    if( this == &copyNode )
    {
        return *this;
    }
    strcpy( aProcessName, copyNode.aProcessName );
    aProcessValue = copyNode.aProcessValue;

    return *this;
}
