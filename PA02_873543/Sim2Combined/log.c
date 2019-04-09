#include <stdio.h>
#include "log.h"
#include "StringUtils.h"


logSettings* currentSettings;


void logToFile( char * message )
{
	FILE *logFile;
	logFile = fopen( currentSettings->logFile, "w" );
	fprintf( logFile, " %s\n", message );
	fclose( logFile );
}

void startLogging(logSettings* settings)
{
	if( currentSettings == NULL )
		{
			settings->logAmount = 0;
			currentSettings = settings;
		}
}

void logLine( char* message)
{
	if( currentSettings->printToLog == True )
		{
			logToFile(message);		
		}
	if( currentSettings->printToMonitor == True )
		{
			printf( "%d: %s\n", message );
		}
}

void stopLogging()
{
	currentSettings = NULL;
}
