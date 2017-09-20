#include "ConfigFileInput.hh"

ConfigFileInput::ConfigFileInput( char* fileName )
{
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
}

ConfigFileInput::~ConfigFileInput( )
{
    ;
}
int ConfigFileInput::GetNumberOfProcesses( )
{
    return aListOfProcesses.GetLength( );
}

int ConfigFileInput::GetProcessValue( const char processName[ ] )
{
    int position = 0;
    while( strcmp( processName, 
            aListOfProcesses.GetEntry( position ).GetProcessName( ) ) != 0
            && position < aListOfProcesses.GetLength( ) )
    {
        ++position;
    }

    if( position >= aListOfProcesses.GetLength( ) )
    {
        return -1;
    }
    return aListOfProcesses.GetEntry( position ).GetProcessValue( );
}
char* ConfigFileInput::GetProcessName( const int position )
{
    return aListOfProcesses.GetEntry( position ).GetProcessName( );
}

char ConfigFileInput::GetLogOutputSpecification( )
{
    return aLogOutputSpecification;
}
char* ConfigFileInput::GetFilePath( )
{
    return aFilePath;
}
char* ConfigFileInput::GetLogFilePath( )
{
    return aLogFilePath;
}

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
    }
    else if( strncmp( lineToParse, "Log File Path:", 14 ) == 0 )
    {
        char tempFileName[ STR_MAX_LENGTH ];
        int position = 0;
        while( lineToParse[ position + 14 ] != '\n' 
                && position < STR_MAX_LENGTH )
        {
            tempFileName[ position ] = lineToParse[ position + 14 ];
            position++;
        }
        tempFileName[ position ] = '\0';

        if( strstr( lineToParse, ".out" ) == NULL )
        {
            cout << "Error in log file path. Incorrect extention. Will "
                 << "only log to moniter." << endl;
            aLogOutputSpecification = 'm';
        }

        strcpy( aLogFilePath, tempFileName ); 

        return true;
    }
    else if( strncmp( lineToParse, "End Sim", 7 ) == 0 )
    {
        return true;
    }
    else
    {
        char tempProcessName[ 30 ] = {'\0'};
        int tempProcessValue = -1;
        char* tempValueToken;
        char* tempNameToken;

        tempValueToken = strpbrk( lineToParse, ":" );
        for( unsigned int i = 0; i < strlen( tempValueToken ) - 2; i++ )
        {
            tempValueToken[ i ] = tempValueToken[ i + 2 ];
        }
        tempValueToken[ strlen( tempValueToken ) - 2 ] = '\0';
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

        aListOfProcesses.InsertEntry( 0, tempNode );

        return true;
    }
} 
