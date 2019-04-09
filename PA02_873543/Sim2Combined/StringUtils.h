//Pre-compiler directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H


//header files
#include <stdio.h> //file operations
#include <stdlib.h> //dynamic memory operations

//create global constants - across files
typedef enum { False, True } Boolean; //this create Boolean type

typedef enum { NO_ERR,
               INCOMPLETE_FILE_ERR,
               INPUT_BUFFER_OVERRUN_ERR } StringManipCode;

extern const int MAX_STR_LEN;

extern const int STD_STR_LEN; //informs the outside world that this is what we want: 
                                //the extern keyword gets it to the outside world
extern const char NULL_CHAR;

extern const int SUBSTRING_NOT_FOUND;

extern const int STR_EQ;

extern const char COLON;

extern const char SPACE;

extern const char SEMICOLON;
extern const char LEFT_PAREN;
extern const char RIGHT_PAREN;

extern const char PERIOD;

extern const Boolean IGNORE_LEADING_WS;

extern const Boolean ACCEPT_LEADING_WS;


//function prototypes
int getStringLength( char *testStr ); //implicit declaration / prototype

void copyString( char *destination, char *source );

void concatenateString( char *destination, char *source );

int compareString ( char *oneStr, char *otherStr );

void getSubString( char *destStr, char *sourceStr,
                                     int startIndex, int endIndex );

int findSubString( char *testStr, char *searchSubStr );

void setStrToLowerCase( char *destStr, char *sourceStr );

char setCharToLowerCase( char testChar );

int getLineTo( FILE *filePtr, int bufferSize, char stopChar,
                            char *buffer, Boolean omitLeadingWhiteSpace );

Boolean isEndOfFile( FILE *filePtr );


#endif //STRING_UTILS_H

