#ifndef LOG_H
#define LOG_H

#include <stdbool.h>

typedef struct logSettings
	{
	bool printToMonitor;
	bool printToLog;
	char* logFile;
	int logAmount;
	} logSettings;

void logLine( char* message );
void startLogging(logSettings* settings);
void stopLogging();

#endif