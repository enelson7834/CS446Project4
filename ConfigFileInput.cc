/**
@file ConfigFileInput.hh
@author Eugene Nelson
@breif The header file for the ConfigFileInput class.
@version    1.0 Eugene Nelson
            Originally developed ( 9 - 19 - 17 )
*/

#include "ConfigFileInput.hh"

/////////////////////////////////////////////////////////////////////////////
// Constructors/Deconstructors
/////////////////////////////////////////////////////////////////////////////
ConfigFileInput::ConfigFileInput( char* fileName )
{
    aLogOutputSpecification = 'E';

    if( strstr( fileName, ".conf" ) == NULL )
    {
        cout << "Error in configuration file path. Incorrect extention." 
             << endl;

        strcpy( aFilePath, "None" );
        aLogOutputSpecification = 'E';
        strcpy( aLogFilePath, "None" );
        return;
    }

    ifstream fin;
    fin.open( fileName );

    if( !fin.good() )
    {
        cout << "Error opening configuration file. Please check the file name"
             << " and run again." << endl;

        strcpy( aFilePath, "None" );
        aLogOutputSpecification = 'E';
        strcpy( aLogFilePath, "None" );
        fin.close( );
        return;
    } 
    else
    {
        bool fileStatus = 1;
        char tempLine[ STR_MAX_LENGTH ];
        fin.getline( tempLine, STR_MAX_LENGTH, '\n' );
        do {
            if( !ParseLine( tempLine ) )
            {
                fileStatus = 0;
            }
            fin.getline( tempLine, STR_MAX_LENGTH, '\n' );
        } while( !fin.eof( ) && fileStatus );
    }

    fin.close();
} // end Default Constructor

ConfigFileInput::ConfigFileInput( const ConfigFileInput& copyInput )
{
    strcpy( aFilePath, copyInput.aFilePath );
    aLogOutputSpecification = copyInput.aLogOutputSpecification;
    strcpy( aLogFilePath, copyInput.aLogFilePath );
    aListOfProcesses = copyInput.aListOfProcesses;
} // end Copy Constructor

ConfigFileInput::~ConfigFileInput( )
{
    ;
} // end Deconstructor
/////////////////////////////////////////////////////////////////////////////

int ConfigFileInput::GetNumberOfProcesses( )
{
    return aListOfProcesses.size( );
} // end GetNumberOfProcesses

/**<
Searches for the specified process name in the list of processes to get it's
value
Simply searches through the list to find the position of the process we are
looking for and uses that position to get the value.

@pre    None.
@post   The value of the process with the given name is returned.
@param  processName The name of the process to search for.
@return The value of the specified process.
****************************************************************************/
int ConfigFileInput::GetProcessValue( const char processName[ ] )
{
    list<ConfigFileInputNode>::iterator it = aListOfProcesses.begin( );
    while( strcmp( processName, 
            it->GetProcessName( ) ) != 0
            && it != aListOfProcesses.end( ) )
    {
        ++it;
    }

    //if( it == NULL )
    //{
        //return -1;
    //}
    return it->GetProcessValue( );
} // end GetProcessValue

char* ConfigFileInput::GetProcessName( const int position )
{
    list<ConfigFileInputNode>::iterator it = aListOfProcesses.begin( );
    for( int i = 1; i < position; i++ )
    {
        ++it;
    }
    
    
    //~ if( it == NULL )
    //~ {
        //~ return '\0';
    //~ }
    return it->GetProcessName( );
} // end GetProcessName

char ConfigFileInput::GetLogOutputSpecification( )
{
    return aLogOutputSpecification;
} // endGetLogOutputSpecification

char* ConfigFileInput::GetFilePath( )
{
    return aFilePath;
} // end GetFilePath

char* ConfigFileInput::GetLogFilePath( )
{
    return aLogFilePath;
} // ennd GetLogFilePath

/**<
Helper function that parses the lines in the config file and stores the 
relevent information.

@pre    None.
@post   The line will be parsed through and the tokens will be extracted
        and saved in the nodes in the list.
@param  lineToParse The line to parse through.
@return The status of the parse line function.
****************************************************************************/
bool ConfigFileInput::ParseLine( char lineToParse[ ] )
{
    if( strncmp( lineToParse, "\n", 1 ) == 0 )
    {
        return false;
    }
    else if( strncmp( lineToParse, "Start Sim", 9 ) == 0 )
    {
        return true;
    } 
    else if( strncmp( lineToParse, "Version", 7 ) == 0 )
    {
        return true;
    }
    else if( strncmp( lineToParse, "File Path:", 10 ) == 0 )
    {
        char tempFileName[ STR_MAX_LENGTH ];
        int position = 0;
        while( lineToParse[ position + 11 ] != '\n' 
                && position < STR_MAX_LENGTH )
        {
            tempFileName[ position ] = lineToParse[ position + 11 ];
            position++;
        }
        tempFileName[ position ] = '\0';

        if( strstr( lineToParse, ".mdf" ) == NULL )
        {
            cout << "Error in test file path. Incorrect extention." << endl;
            return false;
        }

        strcpy( aFilePath, tempFileName ); 

        return true;
    }

    // Retrieve the log specification and check for errors
    /////////////////////////////////////////////////////////////////////////
    else if( strncmp( lineToParse, "Log:", 4 ) == 0 )
    {
        if( aLogOutputSpecification != 'E' )
        {
            return true;
        }

        if( strstr( lineToParse, "Moniter" ) != NULL )
        {
            aLogOutputSpecification = 'M';
        }
        else if( strstr( lineToParse, "File" ) != NULL )
        {
            if( aLogOutputSpecification == 'm' )
            {
                aLogOutputSpecification = 'E';
            }
            else
            {
                aLogOutputSpecification = 'F';
            }
        }
        else if( strstr( lineToParse, "Both" ) != NULL )
        {
            if( aLogOutputSpecification == 'm' )
            {
                aLogOutputSpecification = 'M';
            }
            else
            {
                aLogOutputSpecification = 'B';
            }
        }
        else
        {
            cout << "Error in log specification. No valid specification given."
                 << endl;
            aLogOutputSpecification = 'E';
            return false;
        }

        return true;
    } // end retrieve log output specification

    // Retrieve the log file path and check for errors
    /////////////////////////////////////////////////////////////////////////
    else if( strncmp( lineToParse, "Log File Path:", 14 ) == 0 )
    {
        char tempFileName[ STR_MAX_LENGTH ];
        int position = 0;
        while( lineToParse[ position + 15 ] != '\n' 
                && position < STR_MAX_LENGTH )
        {
            tempFileName[ position ] = lineToParse[ position + 15 ];
            position++;
        }
        tempFileName[ position ] = '\0';

        if( strpbrk( tempFileName, " " ) != NULL )
        {
            cout << "Error in log file path. Improper file name.";
            if( aLogOutputSpecification == 'M' 
                || aLogOutputSpecification == 'B' )
            {
                aLogOutputSpecification = 'M';
                cout << " Will only log to monitor." << endl;
            }
            else
            {
                aLogOutputSpecification = 'E';
                cout << " Will not log." << endl;
            }
        }

        strcpy( aLogFilePath, tempFileName ); 

        return true;
    } // end getting the file path
    else if( strncmp( lineToParse, "End Sim", 7 ) == 0 )
    {
        return true;
    }

    // Retrieve the tokens from process specifications
    /////////////////////////////////////////////////////////////////////////
    else
    {
        char tempProcessName[ 30 ] = {'\0'};
        int tempProcessValue = -1;
        char* tempValueToken;
        char* tempNameToken;

        tempValueToken = strpbrk( lineToParse, ":" );
        RemoveSpaces( tempValueToken );
        AdjustLineElements( tempValueToken , 0 );
        tempProcessValue = atoi( tempValueToken );

        tempNameToken = strtok( lineToParse, " :;" );
        while( strpbrk( tempNameToken, "(" ) == NULL )
        {
            strcat( tempProcessName, tempNameToken );
            strcat( tempProcessName, " " );
            tempNameToken = strtok( NULL, " " );
        }

        int goodToCut = 0;
        for( unsigned int i = strlen( tempProcessName ); i > 0; i-- )
        {
            if( tempProcessName[ i ] == ' ' )
            {
                if( goodToCut == 2 )
                {
                    tempProcessName[ i ] = '\0';
                    goodToCut++;
                } 
                else
                {
                    goodToCut++;
                }
            }
        }

        for( unsigned int i = 0; i < strlen( tempProcessName ); i++ )
        {
           tempProcessName[ i ] = tolower( tempProcessName[ i ] );
        }

        ConfigFileInputNode tempNode( tempProcessName, tempProcessValue );

        aListOfProcesses.insert( aListOfProcesses.end( ), tempNode );

        return true;
    } // end getting tokens
} // end ParseLine

/**<
Helper function to make parsing easier

@pre    None.
@post   The specified string will have all space characters removed.
@param  lineToRemoveSpaces The string who's spaces will be removed.
@return void
****************************************************************************/
void ConfigFileInput::RemoveSpaces( char lineToRemoveSpaces[ ] )
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
void ConfigFileInput::AdjustLineElements(  char lineToAdjust[ ], 
                                        int positionToAdjust )
{
    for( int i = positionToAdjust; i < ( int ) strlen( lineToAdjust ); i++ )
    {
        lineToAdjust[ i ] = lineToAdjust[ i + 1 ];
    }
} // end AdjustLineElements
