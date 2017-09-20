#include <cstring>

#ifndef meta_data_info_node_hh
#define meta_data_info_node_hh

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