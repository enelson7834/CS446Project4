/**
@file MetaDataInfoNode.hh
@author Eugene Nelson
@breif The header for the MetaDataInfoNode class
@version    1.0 Eugene Nelon
            Originally developed ( 9 - 20 - 17 ) 
*/

/////////////////////////////////////////////////////////////////////////////
// Header files
/////////////////////////////////////////////////////////////////////////////
#include <cstring>

/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives
/////////////////////////////////////////////////////////////////////////////
#ifndef meta_data_info_node_hh
#define meta_data_info_node_hh

/////////////////////////////////////////////////////////////////////////////
// Class Definitions
/////////////////////////////////////////////////////////////////////////////
class MetaDataInfoNode
{
    public:
        MetaDataInfoNode( );
        MetaDataInfoNode( const MetaDataInfoNode& copyNode );
        MetaDataInfoNode(   const char newMetaDataCode, 
                            const char newMetaDataDescriptor[ ],
                            const int newNumberOfCycles,
                            const int newErrorCode );
        ~MetaDataInfoNode( );

        char SetMetaDataCode( const char newMetaDataCode );
        char* SetMetaDataDescriptor( const char newMetaDataDescriptor[ ] );
        int SetNumberOfCycles( const int newNumberOfCycles );
        int SetErrorCode( const int newErrorCode );

        char GetMetaDataCode( ) const;
        char* GetMetaDataDescriptor( ) const;
        int GetNumberOfCycles( ) const;
        int GetErrorCode( ) const;

        MetaDataInfoNode& operator=( const MetaDataInfoNode& copyNode );
    private:
        char aMetaDataCode;
        char* aMetaDataDescriptor;
        int aNumberOfCycles;
        int aErrorCode;
};

#endif