#include "MetaDataInfo.hh"

MetaDataInfo::MetaDataInfo( char* fileName )
{
    if( strstr( fileName, ".mdf" ) == NULL )
    {
        cout << "Error reading meta data file: Incorrect extention." << endl;
        return;
    }

    ifstream fin;
    fin.open( fileName );

    if( !fin.good( ) )
    {
        cout << "Error reading meta data file: File not good." << endl;
        fin.close( );
        return;
    }

    bool fileStatus = 1;
    char tempLine[ 300 ] = {'\0'};
    fin.getline( tempLine, 300, '\n' );
    do {
        if( !ParseLine( tempLine ) )
        {
            fileStatus = 0;
        }
        fin.getline( tempLine, 300, '\n' );
    } while( !fin.eof( ) && fileStatus );

    fin.close();
}
MetaDataInfo::~MetaDataInfo( )
{
    ;
}

void MetaDataInfo::processData( ConfigFileInput configFile )
{
    char logSpecification = configFile.GetLogOutputSpecification( );
    ofstream logFile;
    if( logSpecification == 'F' || logSpecification == 'B' ) 
    {
        logFile.open( configFile.GetLogFilePath( ) );
        if( !logFile.good( ) )
        {
            cout << "Error creating LogFile. Please try again." << endl;
            logFile.close();
            return;
        }    
    }

    LinkedQueue<MetaDataInfoNode> tempStorageQueue( );

    char tempMessage[ 500 ];
    char tempProcessName[ 30 ];
    char tempProcessValue[ 5 ];

    tempMessage = {"Configuration File Data:\n"};

    LogOutput( logSpecification, tempMessage, logFile );
    for( int i = 0; i < configFile.GetNumberOfProcesses( ); i++ )
    {
        tempMessage[ 0 ] = '\0';
        strcpy( tempProcessName, configFile.GetProcessName( i ) );
        itoa(   configFile.GetProcessValue( tempProcessName ), 
                tempProcessValue, 10 );

        for( int j = 0; j < (int) strlen( tempProcessName ); j++ );
        {
            if( j == 0 || tempProcessName[ j - 1 ] == " " )
            {
                tempProcessName[ j ] = toupper( tempProcessName[ j ] );
            }
        }

        strcat( tempMessage, tempProcessName );
        strcat( tempMessage, " = " );
        strcat( tempMessage, tempProcessValue );

        if( strcmp( tempProcessName, "System" ) == 0 )
        {
            strcat( tempMessage, " kbytes\n" );
        }
        else
        {
            strcat( tempMessage, " ms/cycle\n" );
        }

        LogOutput( logSpecification, tempMessage, logFile ); 
    }

    strcpy( tempMessage, "Logged to: " );
    if( logSpecification == 'M' || logSpecification == 'B' )
    {
        strcat( tempMessage, "monitor" );
    }
    else if( logSpecification == 'B' )
    {
        strcat( tempMessage, " and " );
    }
    else if( logSpecification == 'F' || logSpecification == 'B' )
    {
        strcat( tempMessage, configFile.GetLogFilePath( ) );
    }
    else
    {
        strcat( tempMessage, "None" );
    }
    strcat( tempMessage, "\n\nMeta-Data Metrics\n" );

    LogOutput( logSpecification, tempMessage, logFile ); 

    char* tempToken;
    char tempMetaDataCode = '\0';
    char tempMetaDataDescriptor[ 30 ];
    int tempNumberOfCycles = 0;
    int tempProcessRunTime = 0;
    int tempErrorCode = 0;

    while( !aQueueOfMetaData.IsEmpty( ) )
    {
        tempMetaDataCode = '\0';
        tempMetaDataDescriptor[ 0 ] = '\0';
        tempNumberOfCycles = 0;
        tempProcessRunTime = 0;
        tempErrorCode = 0;
        tempMessage[ 0 ] = '\0';

        tempMetaDataCode = aQueueOfMetaData.PeekFront( ).GetMetaDataCode( );
        strcpy(    tempMetaDataDescriptor, 
                    aQueueOfMetaData.PeekFront( ).GetMetaDataDescriptor( ) );
        tempNumberOfCycles = aQueueOfMetaData.
                                            PeekFront( ).GetNumberOfCycles( );
        tempErrorCode = aQueueOfMetaData.PeekFront( ).GetErrorCode( );
        if( tempErrorCode != 0 )
        {
            ProcessErrorCode( logSpecification, tempErrorCode, logFile );
        }

        switch( tempMetaDataCode )
        {
            case 'S':
                if( strcmp( tempMetaDataDescriptor, "start" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
                        ;
                    }
                    else
                    {
                        tempErrorCode = 51;
                    }
                }
                else if( strcmp( tempMetaDataDescriptor, "end" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
                        return;
                    }
                }
                else
                {
                    tempErrorCode = 41;
                }

                break;
            case 'A':
                if( strcmp( tempMetaDataDescriptor, "start" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
                        ;
                    }
                    else
                    {
                        tempErrorCode = 51;
                    }
                }
                else if( strcmp( tempMetaDataDescriptor, "end" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
                        ;
                    }
                    else
                    {
                        tempErrorCode = 51;
                    }
                }
                else
                {
                    tempErrorCode = 41;
                }

                break;
            case 'P':
                if( strcmp( tempMetaDataDescriptor, "run" ) == 0 )
                {
                    tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.GetProcessValue( "processor" );
                }
                else
                {
                    tempErrorCode = 51;
                }

                break;
            case 'I':
                if( tempNumberOfCycles != 0 )
                {
                    if( configFile.GetProcessValue( tempMetaDataDescriptor ) 
                        == -1 )
                    {
                        tempErrorCode = 41;
                    }
                    else
                    {
                        tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.
                                    GetProcessValue( tempMetaDataDescriptor );
                    }
                }
                else
                {
                    tempErrorCode = 41;
                }

                break;
            case 'O':
                if( tempNumberOfCycles != 0 )
                {
                    if( configFile.GetProcessValue( tempMetaDataDescriptor ) 
                        == -1 )
                    {
                        tempErrorCode = 41;
                    }
                    else
                    {
                        tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.
                                    GetProcessValue( tempMetaDataDescriptor );
                    }
                }
                else
                {
                    tempErrorCode = 41;
                }

                break;
            case 'M':
                if( strcmp( tempMetaDataDescriptor, "block" ) == 0 )
                {
                    if( tempNumberOfCycles > 0 )
                    {
                        ;
                    }
                    else
                    {
                        tempErrorCode = 51;
                    }
                }
                else if( strcmp( tempMetaDataDescriptor, "allocate" ) == 0 )
                {
                    if( tempNumberOfCycles > 0 )
                    {
                        ;
                    }
                    else
                    {
                        tempErrorCode = 51;
                    }
                }
                else
                {
                    tempErrorCode = 41;
                }

                break;
            default:
                tempErrorCode = 31;

        }

        if( tempErrorCode == 0 )
        {
            if( tempProcessRunTime > 0 )
            {
                itoa( tempProcessRunTime, tempToken, 10 );

                tempMessage[ 0 ] = tempMetaDataCode;
                strcat( tempMessage, "(" );
                strcat( tempMessage, tempMetaDataDescriptor );
                strcat( tempMessage, ") - " );
                strcat( tempMessage, tempToken );
                strcat( tempMessage, " ms\n" );

                LogOutput( logSpecification, tempMessage, logFile );
            }
            else
            {
                ;
            }
        }
        else
        {
            ProcessErrorCode( logSpecification, tempErrorCode, logFile );
        }

        tempStorageQueue.Enqueue( aQueueOfMetaData.PeekFront( ) );
        aQueueOfMetaData.Dequeue( );
    }

    logFile.close( );

    while( !tempStorageQueue.IsEmpty( ) )
    {
        aQueueOfMetaData.Enqueue( tempStorageQueue.PeekFront( ) );
        tempStorageQueue.Dequeue( ); 
    }
}

bool MetaDataInfo::ParseLine( char lineToParse[ ] )
{
    if( strncmp( lineToParse, "Start", 5 ) )
    {
        return true;
    }
    else if( strncmp( lineToParse, "End", 3 ) )
    {
        return true;
    }
    else
    {
        char tempHelper[ 300 ] = {'\0'};
        char* tempHelperPtr = new char[ 300 ];
        char* tempHelperPtrAnchor = tempHelperPtr;
        char tempMetaDataCode = '\0';
        char tempMetaDataDescriptor[ 30 ] = {'\0'};
        int tempNumberOfCycles = -1;
        int tempErrorCode = 0;
        MetaDataInfoNode tempNode;

        RemoveSpaces( lineToParse );
        strcpy( tempHelper, lineToParse );
        strcpy( tempHelperPtr, tempHelper );

        int iterator = 0;
        while( tempHelperPtr != NULL )
        {
            tempMetaDataCode = '\0';
            tempMetaDataDescriptor[ 0 ] = '\0';
            tempNumberOfCycles = -1;
            tempErrorCode = 0;

            tempHelperPtr = strtok( tempHelperPtr, ".,:;\0" );
            tempHelperPtr = strtok( tempHelperPtr, "(" );

            tempMetaDataCode = ( tempHelperPtr[ 0 ] );
            if( tempMetaDataCode == '\0' )
            {
                tempErrorCode = 33;
            }
            else if( tempMetaDataCode > 'Z' || tempMetaDataCode < 'A' )
            {
                tempErrorCode = 32;
            }

            tempHelperPtr = strtok( NULL, ")" );
            if( tempHelperPtr == NULL )
            {
                tempErrorCode = 42;
            }
            else
            {
                strcpy( tempMetaDataDescriptor, tempHelperPtr );
            }

            tempHelperPtr = strtok( NULL, ":" );
            if( tempHelperPtr == NULL )
            {
                tempErrorCode = 53;
            }
            else if( tempHelperPtr[ 0 ] > '9' || tempHelperPtr[ 0 ] < '0' )
            {
                tempErrorCode = 54;
            }
            else
            {
                tempNumberOfCycles = atoi( tempHelperPtr );
            }

            if( tempNumberOfCycles < 0 )
            {
                tempErrorCode = 52;
            }
            
            tempNode.SetMetaDataCode( tempMetaDataCode );
            tempNode.SetMetaDataDescriptor( tempMetaDataDescriptor );
            tempNode.SetNumberOfCycles( tempNumberOfCycles );
            tempNode.SetErrorCode( tempErrorCode );
            aQueueOfMetaData.Enqueue( tempNode );

            tempHelperPtr = tempHelperPtrAnchor;
            strcpy( tempHelperPtr, tempHelper );
            tempHelperPtr = strtok( tempHelperPtr, ".,:;\0" );

            for( int i = 0; i < iterator; i++ )
            {
                tempHelperPtr = strtok( NULL, ",.:;\0" );
            }

            tempHelperPtr = strtok( NULL, "\0" );

            iterator++;
        }

        delete tempHelperPtr;
        tempHelperPtr = NULL;
        tempHelperPtrAnchor = NULL;

        return true;
    }
}

void MetaDataInfo::RemoveSpaces( char lineToRemoveSpaces[ ] )
{
    for( int i = 0; i < ( int ) strlen( lineToRemoveSpaces ); i++ )
    {
        if( lineToRemoveSpaces[ i ] == '(' )
        {
            for( int j = i; j < ( int ) strlen( lineToRemoveSpaces ); j++ )
            {
                if( lineToRemoveSpaces[ j ] == ')' )
                {
                    i = j;
                    break;
                }
            }
        }
        if( lineToRemoveSpaces[ i ] == ' ' )
        {
            AdjustLineElements( lineToRemoveSpaces, i );
        }
    }
}
void MetaDataInfo::AdjustLineElements(  char lineToAdjust[ ], 
                                        int positionToAdjust )
{
    for( int i = positionToAdjust; i < ( int ) strlen( lineToAdjust ); i++ )
    {
        lineToAdjust[ i ] = lineToAdjust[ i + 1 ];
    }
}
void MetaDataInfo::ProcessErrorCode(    char logSpecification, 
                                        char errorCode, 
                                        ofstream& logFile )
{
    char tempMessage[ 30 ] = {'\0'};
    switch( errorCode )
    {
        case 21:
            strcpy( tempMessage, "Error in pasring function.\n" );
            break;
        case 31:
            strcpy( tempMessage, "Error in meta data code.\n" );
            break;
        case 32:
            strcpy( tempMessage, "Error: Meta data code is wrong case or " );
            strcat( tempMessage, "non-alphabetic\n" );
            break;
        case 33:
            strcpy( tempMessage, "Error: Meta data code is missing.\n" );
            break;
        case 41:
            strcpy( tempMessage, "Error: Error in meta data descriptor.\n" );
            break;
        case 42:
            strcpy( tempMessage, "Error: Meta data descriptor missing.\n" );
            break;
        case 51:
            strcpy( tempMessage, "Error in cycle value.\n" );
            break;
        case 52:
            strcpy( tempMessage, "Error: Cycle value is negative.\n" );
            break;
        case 53:
            strcpy( tempMessage, "Error: Cycle value is negative.\n" );
            break;
        case 54:
            strcpy( tempMessage, "Error: Cycle valye is not numeric.\n" );
            break;
        case 61:
            strcpy( tempMessage, "Error in pasring function.\n" );
            break;
        default:
            strcpy( tempMessage, "Error: An unknown error occured.\n" );
            break;
    }

    LogOutput( logSpecification, tempMessage, logFile );
}


void MetaDataInfo::LogOutput(   char logSpecification, 
                                char* logMessage, 
                                ofstream& logFile )
{
    if( logSpecification == 'M' || logSpecification == 'B' )
    {
        cout << logMessage;
    }
    else if( logSpecification == 'F' || logSpecification == 'B' )
    {
        logFile << logMessage;
    }
    else
    {
        ;
    }
}