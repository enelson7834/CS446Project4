/**
@file MetaDataInfo.cc
@author Eugene Nelson
@breif The implamentation file for the MetaDataInfo class.
@version    1.0 Eugene Nelson
            Originally developed ( 9 - 19 - 17 )
*/

#include "MetaDataInfo.hh"

/////////////////////////////////////////////////////////////////////////////
// Constructors/Deconstructors
/////////////////////////////////////////////////////////////////////////////
MetaDataInfo::MetaDataInfo( char* fileName )
{
	cout << fixed;
	cout << setprecision( 6 ); 
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

    aQueueOfMetaData.pop( );

    fin.close();
} // end Constructor

MetaDataInfo::~MetaDataInfo( )
{
    ;
} // end Deconstructor

/**<
Processes the data from the Meta Data file and logs it to appropriate output

@pre ConfigFile has all necessary information to process.
@post Simulation will have been run and output logged to appropriate outlets.
@param configFile   The configuration file with necessary info to preform
                    the simulation.
@return void
****************************************************************************/
void MetaDataInfo::ProcessData( ConfigFileInput& configFile,
								PCB& state,
								timeval& initTime )
{
    // Variable declarations/initialization
    /////////////////////////////////////////////////////////////////////////
    char tempLogFilePath[ 30 ];
    char tempLogDirectory[ 30 ];
    char* tempLogFilePathPtr;
    char logSpecification = configFile.GetLogOutputSpecification( );

    strcpy( tempLogFilePath, configFile.GetLogFilePath( ) );
    if( logSpecification == 'F' || logSpecification == 'B' ) 
    {
        if( strpbrk( tempLogFilePath, "/" ) != NULL )
        {
            tempLogFilePathPtr = strtok( tempLogFilePath, "/" );
            strcpy( tempLogDirectory, "mkdir -p " );
            strcat( tempLogDirectory, tempLogFilePathPtr );

            const int dir_err = system( tempLogDirectory );
            if( -1 == dir_err )
            {
                cout << "Error creating directory." << endl;
                exit(1);
            }
        }   
    }

    ofstream logFile( configFile.GetLogFilePath( ) );
    if( !logFile.good( ) )
    {
        cout << "Error creating LogFile. Please try again." << endl;
        logFile.close();
        return;
    } 

    char tempMessage[ 500 ];
    
    /*
    char tempProcessName[ 30 ];
    char tempProcessValue[ 5 ];
	*/
	
    gettimeofday( &initTime, NULL );

    if( state.processState == 1 )
    {
    	LogTime( logSpecification, timer( 1, initTime ), logFile );
    	strcpy( tempMessage, " - Simulator program starting\n" );
    	LogOutput( logSpecification, tempMessage, logFile);
    	state.processState++;
    }

    queue<MetaDataInfoNode> tempStorageQueue;
    /*
    // Process the Configuration Data to output to Log
    /////////////////////////////////////////////////////////////////////////
    for( int i = 1; i < configFile.GetNumberOfProcesses( ) + 1; i++ )
    {
        tempMessage[ 0 ] = '\0';
        strcpy( tempProcessName, configFile.GetProcessName( i ) );
        itoa(   configFile.GetProcessValue( tempProcessName ), 
                tempProcessValue, 10 );

        for( int j = 0; j < (int) strlen( tempProcessName ); j++ )
        {
            if( j == 0 || tempProcessName[ j - 1 ] == ' ' )
            {
                tempProcessName[ j ] = toupper( tempProcessName[ j ] );
            }
        }

        strcat( tempMessage, tempProcessName );
        strcat( tempMessage, " = " );
        strcat( tempMessage, tempProcessValue );

        if( strncmp( tempProcessName, "System", 6 ) == 0 )
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
    if( logSpecification == 'B' )
    {
        strcat( tempMessage, " and " );
    }
    if( logSpecification == 'F' || logSpecification == 'B' )
    {
        strcat( tempMessage, configFile.GetLogFilePath( ) );
    }

    strcat( tempMessage, "\n\nMeta-Data Metrics\n" );
    LogOutput( logSpecification, tempMessage, logFile ); 
    */
    // More Variable Initializations for processing the Meta Data
    /////////////////////////////////////////////////////////////////////////

    char tempToken[ 10 ];
    char tempToken2[ 10 ];
    char tempMetaDataCode = '\0';
    char tempMetaDataDescriptor[ 30 ];
    int tempNumberOfCycles = 0;
    int tempProcessRunTime = 0;
    int tempErrorCode = 0;

    // Begin processing Meta Data
    /////////////////////////////////////////////////////////////////////////

    while( !aQueueOfMetaData.empty( ) )
    {
        tempMetaDataCode = '\0';
        tempMetaDataDescriptor[ 0 ] = '\0';
        tempNumberOfCycles = 0;
        tempProcessRunTime = 0;
        tempErrorCode = 0;

        // Load Meta Data info into buffers
        /////////////////////////////////////////////////////////////////////
        tempMetaDataCode = aQueueOfMetaData.front( ).aMetaDataCode;
        strcpy(    tempMetaDataDescriptor, 
                    aQueueOfMetaData.front( ).aMetaDataDescriptor );
        tempNumberOfCycles = aQueueOfMetaData.
                                            front( ).aNumberOfCycles;
        tempErrorCode = aQueueOfMetaData.front( ).aErrorCode;

        if( tempErrorCode != 0 )
        {
            ProcessErrorCode( logSpecification, tempErrorCode, logFile );
        }

        // Check that code match with appropriate descriptor and get runtime
        /////////////////////////////////////////////////////////////////////
        switch( tempMetaDataCode )
        {
            case 'S':
                if( strcmp( tempMetaDataDescriptor, "start" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
					    // Move PCB to READY mode
					    if( state.processState == 2 )
					    {
					    	LogTime( logSpecification, timer( 0, initTime ), logFile );
					    	strcpy( tempMessage, " - OS: perparing process 1\n" );
					    	LogOutput( logSpecification, tempMessage, logFile);
					    	state.processState++;
					    }
                    }
                    else									
                        tempErrorCode = 51;
                }
                else if( strcmp( tempMetaDataDescriptor, "end" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                        return;
                }
                else
                    tempErrorCode = 41;

                break;
            case 'A':
                if( strcmp( tempMetaDataDescriptor, "start" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
					    // Move PCB to RUNNING mode
					    if( state.processState == 3 )
					    {
					    	LogTime( logSpecification, timer( 0, initTime ), logFile );
					    	strcpy( tempMessage, " - OS starting process 1\n" );
					    	LogOutput( logSpecification, tempMessage, logFile);
					    	state.processState++;
					    }
                    }
                    else
                        tempErrorCode = 51;
                }
                else if( strcmp( tempMetaDataDescriptor, "end" ) == 0 )
                {
                    if( tempNumberOfCycles == 0 )
                    {
              			// Move PCB to EXIT mode
					    if( state.processState == 3 )
					    {
					    	LogTime( logSpecification, timer( 0, initTime ), logFile );
					    	strcpy( tempMessage, " - OS removing process 1\n" );
					    	LogOutput( logSpecification, tempMessage, logFile);
					    	state.processState = 5;
					    }	
                    }
                    else
                        tempErrorCode = 51;
                }
                else
                    tempErrorCode = 41;

                break;
            case 'P':
                if( strcmp( tempMetaDataDescriptor, "run" ) == 0 )
                {
                    tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.GetProcessValue( "processor" );
				    if( state.processState == 3 )
				    {
				    	LogTime( logSpecification, timer( 0, initTime ), logFile );
				    	strcpy( tempMessage, " - start processing action\n" );
				    	LogOutput( logSpecification, tempMessage, logFile);
				    	
				    	LogTime( logSpecification, timer( tempProcessRunTime, initTime ), logFile );
				    	strcpy( tempMessage, " - end processing action\n" );
				    	LogOutput( logSpecification, tempMessage, logFile);
				    }	
                }
                else
                    tempErrorCode = 51;

                break;
            case 'I':
                if( tempNumberOfCycles != 0 )
                {
                    if( configFile.GetProcessValue( tempMetaDataDescriptor ) 
                        == -1 )
                        tempErrorCode = 41;
                    else
                        tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.
                                    GetProcessValue( tempMetaDataDescriptor );
                }
                else
                    tempErrorCode = 41;

                break;
            case 'O':
                if( tempNumberOfCycles != 0 )
                {
                    if( configFile.GetProcessValue( tempMetaDataDescriptor ) 
                        == -1 )
                        tempErrorCode = 41;
                    else
                        tempProcessRunTime = tempNumberOfCycles * 
                                    configFile.
                                    GetProcessValue( tempMetaDataDescriptor );
                }
                else
                    tempErrorCode = 41;

                break;
            case 'M':
                if( strcmp( tempMetaDataDescriptor, "block" ) == 0 )
                {
                    if( tempNumberOfCycles > 0 )
                        tempProcessRunTime = tempNumberOfCycles *
                                    configFile.
                                    GetProcessValue( "memory" );
                    else
                        tempErrorCode = 51;
                }
                else if( strcmp( tempMetaDataDescriptor, "allocate" ) == 0 )
                {
                    if( tempNumberOfCycles > 0 )
                        tempProcessRunTime = tempNumberOfCycles *
                                        configFile.
                                        GetProcessValue( "memory" );
                    else
                        tempErrorCode = 51;
                }
                else
                    tempErrorCode = 41;

                break;
            default:
                tempErrorCode = 31;

        }

        // Prepare the line for the Log output
        /////////////////////////////////////////////////////////////////////
        /*if( tempErrorCode == 0 )
        {
            if( tempProcessRunTime > 0 )
            {
                itoa( tempProcessRunTime, tempToken, 10 );
                itoa( tempNumberOfCycles, tempToken2, 10 );

                tempMessage[ 0 ] = tempMetaDataCode;
                tempMessage[ 1 ] = '\0';
                strcat( tempMessage, "(" );
                strcat( tempMessage, tempMetaDataDescriptor );
                strcat( tempMessage, ")" );
                strcat( tempMessage, tempToken2 );
                strcat( tempMessage, " - " );
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
        */

        tempStorageQueue.push( ( aQueueOfMetaData.front( ) ) );
        aQueueOfMetaData.pop( );
    }

    logFile.close( );

    // Return queue to original state
    /////////////////////////////////////////////////////////////////////////
    while( !tempStorageQueue.empty( ) )
    {
        aQueueOfMetaData.push( ( tempStorageQueue.front( ) ) );
        tempStorageQueue.pop( ); 
    }
} // End ParseData

/**<
Parses the line from Meta Data and stores the tokens in nodes in the queue

@pre None.
@post   Meta Data line will be parsed and all important information will be
        stored in nodes within the queue of processes to be simulated later.
@param lineToParse  The line from the MetaData file that will be parsed
@return The status of the parse, indicating errors in the parsing process.
@note   Will also set error codes for any potentially troublesome processes
        so that they may be delt with later, without crashing the program.
****************************************************************************/
bool MetaDataInfo::ParseLine( char lineToParse[ ] )
{
    // Variable declarations/initialization
    /////////////////////////////////////////////////////////////////////////
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

    // Begin parsing the line
    /////////////////////////////////////////////////////////////////////////
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
                
        tempNode.aMetaDataCode = tempMetaDataCode;
        strcpy( tempNode.aMetaDataDescriptor, tempMetaDataDescriptor );
        tempNode.aNumberOfCycles = tempNumberOfCycles;
        tempNode.aErrorCode = tempErrorCode;

        aQueueOfMetaData.push( tempNode );
        
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

    delete tempHelperPtrAnchor;

    tempHelperPtr = NULL;
    tempHelperPtrAnchor = NULL;

    return true;
} // end ParseLine

/**<
Helper function to make parsing easier

@pre    None.
@post   The specified string will have all space characters removed.
@param  lineToRemoveSpaces The string who's spaces will be removed.
@return void
****************************************************************************/
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
} // end RemoveSpaces

/**<
Helper function to make removing spaces easier

@pre    None.
@post   The specified string will have all leading characters from the
        position specified moved back one space.
@param  lineToAdjust The line that will be adjusted.
@param  positionToAdjust The position in the string to which we are
        adjusting.
@return void
****************************************************************************/
void MetaDataInfo::AdjustLineElements(  char lineToAdjust[ ], 
                                        int positionToAdjust )
{
    for( int i = positionToAdjust; i < ( int ) strlen( lineToAdjust ); i++ )
    {
        lineToAdjust[ i ] = lineToAdjust[ i + 1 ];
    }
} // end AdjustLineElements

/**<
Helper function make dealing with errors easier

@pre    None.
@post   The specified error code will be handled and logged appropriately.
@param  logSpecification The specification code indicating where to log
        error.
@param  errorCode The code that needs to be handled.
@param  logFile The file where the error will be logged if specified to log
        to file.
@return void
****************************************************************************/
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

/**<
Helper function to make logging messages easier

@pre    None.
@post   The message to be logged will be logged to the appropriate
        destinations.
@param  logSpecification The specification code indicating where to log
        error.
@param  logMessage The message that needs to be logged.
@param  logFile The file where the error will be logged if specified to log
        to file.
@return void
****************************************************************************/
void MetaDataInfo::LogOutput(   char logSpecification, 
                                char* logMessage, 
                                ofstream& logFile )
{
    if( logSpecification == 'M' 
        || logSpecification == 'B' 
        || logSpecification == 'm' )
    {
        cout << logMessage;
    }
    if( logSpecification == 'F' || logSpecification == 'B' )
    {
        logFile << logMessage;
    }
} // end LogOutput

/**<
Helper function to convert from an integer to a string

@pre    None.
@post   The integer value passed into the function will be converted into
        a string representation to make logging easier.
@param  inputValue The integer value that will be converted to a string.
@param  ouputString The string where the converted value will be stored.
@param  base The base to convert to. i.e. 10 = decimal, 16 = hexadecimal.
@return void
****************************************************************************/ 
void MetaDataInfo::itoa( int inputValue, char* outputString, int base )
{
    int i = 0;
    bool isNegative = false;

    if( inputValue == 0 )
    {
        outputString[ i++ ] = '0';
        outputString[ i ] = '\0';
        return;
    }
    else if( inputValue < 0 )
    {
        isNegative = true;
        inputValue *= -1;
    }

    while( inputValue != 0 )
    {
        int temp = inputValue % base;
        outputString[i++] = ( temp > 9 )? ( temp - 10 ) + 'a' : temp + '0';
        inputValue /= base;
    }

    if( isNegative )
    {
        outputString[ i++ ] = '-';
    }

    outputString[ i-- ] = '\0';

    ReverseString( outputString, i );

    return;
} // end itoa

/**<
Helper function to make converting from int to string easier. 

@pre    None.
@post   The string passed in will be reversed.
@param  string The string to be reversed.
@param  size The size of the string passed in.
@return void
****************************************************************************/ 
void MetaDataInfo::ReverseString( char* string, int size )
{
    char buffer;
    for( int i = size; i > size/2; i-- )
    {
        buffer = string[ i ];
        string[ i ] = string[ size - i ];
        string[ size - i ] = buffer;
    }
} // end ReverseString
void MetaDataInfo::LogTime( 	char logSpecification, 
                        		double time,
                        		ofstream& logFile )
{
    if( logSpecification == 'M' 
        || logSpecification == 'B' 
        || logSpecification == 'm' )
    {
        cout << time;
    }
    if( logSpecification == 'F' || logSpecification == 'B' )
    {
        logFile << time;
    }
}
double MetaDataInfo::timer( long long timeToWait, timeval& initTime )
{
	double time = 0;

	timeval start, end;
	gettimeofday( &start, NULL );
	gettimeofday( &end, NULL );


	while ( ( end.tv_usec - start.tv_usec ) < timeToWait )
		gettimeofday( &end, NULL );


	gettimeofday( &end, NULL );

	int sec, usec;

	sec =  end.tv_sec - initTime.tv_sec;
	usec = end.tv_usec - initTime.tv_usec; 

	if( usec < 0 )
	{
		usec += 1000000;
		sec -= 1;
	}

	time += (double) ( sec + (double)usec/1000000 );

	return time;
}
