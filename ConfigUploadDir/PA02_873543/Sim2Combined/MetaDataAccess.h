#ifndef META_DATA_ACCESS_H
#define META_DATA_ACCESS_H


//header files
#include <stdio.h>
#include "StringUtils.h"


typedef enum {MD_FILE_ACCESS_ERR = 3,
				  MD_CORRUPT_DESCRIPTOR_ERR,
				  OPCMD_ACCESS_ERR,
				  CORRUPT_OPCMD_LETTER_ERR,
				  CORRUPT_OPCMD_NAME_ERR,
				  CORRUPT_OPCMD_VALUE_ERR,
				  UNBALANCED_START_END_ERR,
				  COMPLETE_OPCMD_FOUND_MSG,
				  LAST_OPCMD_FOUND_MSG } OpCodeMessages;


typedef struct OpCodeType
   {
      char opLtr;
      char *opName[ 100 ];
      int opValue;

      struct OpCodeType *next;
   } OpCodeType;


int getOpCodes( char *fileName, OpCodeType **opCodeDataHead );

//int getOpCommand( FILE *filePtr, OpCodeType );

void displayMetaData( OpCodeType *localPtr );

void displayMetaDataError( int code );

OpCodeType *clearMetaDataList( OpCodeType *localPtr );

Boolean isDigit( char testChar );

Boolean checkOpString( char *testStr );

OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode );

int updateEndCount( int count, char *opString );

int updateStartCount( int count, char *opString );


#endif //META_DATA_ACCESS_H