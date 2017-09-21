/**
@file MetaDataInfo.hh
@author Eugene Nelson
@breif The header file for the MetaDataInfo class.
@version    1.0 Eugene Nelson
            Originally developed ( 9 - 19 - 17 )
*/
/////////////////////////////////////////////////////////////////////////////
// Precompiler Directives 
/////////////////////////////////////////////////////////////////////////////
#ifndef meta_data_info_hh
#define meta_data_info_hh

/////////////////////////////////////////////////////////////////////////////
// Constant Definition 
/////////////////////////////////////////////////////////////////////////////
#define LINE_MAX_LEGNTH 300
#define MESSAGE_MAX_LENGTH 500

/////////////////////////////////////////////////////////////////////////////
// Header Files
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>

#include "MetaDataInfoNode.hh"
#include "LinkedQueue.hh"
#include "ConfigFileInput.hh"

/////////////////////////////////////////////////////////////////////////////
// Class Definition
/////////////////////////////////////////////////////////////////////////////
class MetaDataInfo
{
    public:
        MetaDataInfo( char* fileName );
        ~MetaDataInfo( );

        void ProcessData( ConfigFileInput& configFile );
    protected:
        bool ParseLine( char lineToParse[ ] );
        void RemoveSpaces( char lineToRemoveSpaces[ ] );
        void AdjustLineElements( char lineToAdjust[ ], int positionToAdjust );
        void ProcessErrorCode(  char logSpecification, 
                                char errorCode, 
                                ofstream& logFile );
        void LogOutput( char logSpecification, char* logMessage, 
                        ofstream& logFile );
        void itoa( int inputValue, char* outputString, int base );
        void ReverseString( char* string, int size );
    private:
        LinkedQueue<MetaDataInfoNode>* aQueueOfMetaData;
};

#endif