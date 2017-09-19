#include "ConfigFileInput.hh"

ConfigFileInput::ConfigFileInput( char* fileName )
{
    if( strpbrk( fileName, ".conf" ) == NULL )
    {
        cout << "Error in configuration file path. Incorrect extention." 
             << endl;

        strcpy( aFilePath, "None" );
        aLogOutputSpecification = 'e';
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
        aLogOutputSpecification = 'e';
        strcpy( aLogFilePath, "None" );
    } 
    else
    {
        bool fileStatus = 1;
        char tempLine[ STR_MAX_LENGTH ];
        fin.getline( tempLine, STR_MAX_LENGTH, '\n' );
        do {
            cout << tempLine << endl;
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

int ConfigFileInput::GetProcessValue( const char processName[ ] )
{
    int position = 0;
    while( strcmp( processName, 
            aListOfProcesses.GetEntry( position ).GetProcessName( ) ) != 0
            && position < aListOfProcesses.GetLength( ) )
    {
        ++position;
    }

    return aListOfProcesses.GetEntry( position ).GetProcessValue( );
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

        if( strpbrk( lineToParse, ".mdf" ) == NULL )
        {
            cout << "Error in test file path. Incorrect extention." << endl;
            return false;
        }

        strcpy( aFilePath, tempFileName ); 

        return true;
    }
    else if( strncmp( lineToParse, "Log:", 4 ) == 0 )
    {
        if( strstr( lineToParse, "Moniter" ) != NULL )
        {
            aLogOutputSpecification = 'M';
        }
        else if( strstr( lineToParse, "File" ) != NULL )
        {
            aLogOutputSpecification = 'F';
        }
        else if( strstr( lineToParse, "Both" ) != NULL )
        {
            aLogOutputSpecification = 'B';
        }
        else
        {
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

        if( strpbrk( lineToParse, ".out" ) == NULL )
        {
            cout << "Error in log file path. Incorrect extention." << endl;
            return false;
        }

        strcpy( aLogFilePath, tempFileName ); 

        return true;
    }
    else if( strncmp( lineToParse, "End Sim", 7 ) == 0 )
    {
        return true;
    }
    else if( strcmp( lineToParse, "\n" ) == 0 )
    {
        return true;
    }
    else
    {
        char tempProcessName[ 30 ] = {'\0'};
        int tempProcessValue = 0;
        char* tempValueToken;
        char* tempNameToken;

        tempValueToken = strpbrk( lineToParse, ":" );
        for( unsigned int i = 0; i < strlen( tempValueToken ) - 2; i++ )
        {
            tempValueToken[ i ] = tempValueToken[ i + 2 ];
        }
        tempValueToken[ strlen( tempValueToken ) - 2 ] = '\0';
        tempProcessValue = atoi( tempValueToken );

        tempNameToken = strtok( lineToParse, " " );
        while(  strncmp( tempNameToken, "cycle", 5 ) != 0   &&
                strncmp( tempNameToken, "display", 7 ) != 0 &&
                strncmp( tempNameToken, "memory", 6 ) != 0      )
        {
            strcat( tempProcessName, tempNameToken );
            strcat( tempProcessName, " " );
            tempNameToken = strtok( NULL, " " );
        }

        tempProcessName[ strlen( tempProcessName ) - 1 ] = '\0';
        tempProcessName[ 0 ] = tolower( tempProcessName[ 0 ] );

        ConfigFileInputNode tempNode( tempProcessName, tempProcessValue );

        aListOfProcesses.InsertEntry( 0, tempNode );

        return true;
    }
} 
