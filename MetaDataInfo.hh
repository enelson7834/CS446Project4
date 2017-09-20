#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "MetaDataInfoNode.hh"
#include "LinkedQueue.hh"
#include "ConfigFileInput.hh"

#ifndef meta_data_info_hh
#define meta_data_info_hh

#define LINE_MAX_LEGNTH 300
#define MESSAGE_MAX_LENGTH 500

class MetaDataInfo
{
    public:
        MetaDataInfo( char* fileName );
        ~MetaDataInfo( );

        void processData( ConfigFileInput configFile );
    protected:
        bool ParseLine( char lineToParse[ ] );
        void RemoveSpaces( char lineToRemoveSpaces[ ] );
        void AdjustLineElements( char lineToAdjust[ ], int positionToAdjust );
        void ProcessErrorCode(  char logSpecification, 
                                char errorCode, 
                                ofstream& logFile );
        void LogOutput( char logSpecification, char* logMessage, 
                        ofstream& logFile );
    private:
        LinkedQueue<MetaDataInfoNode> aQueueOfMetaData;
};

#endif