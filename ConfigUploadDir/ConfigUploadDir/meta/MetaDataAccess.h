//header files
#include <stdio.h>
#include "StringUtils.h"

typedef struct OpCodeType
   {
      char opLtr;
      char opName[ 100 ];
      int opValue;

      struct OpCodeType *next;
   } OpCodeType;

void displayMetaData( OpCodeType *localPtr );

int getOpCodes( char *fileName, OpCodeType **opCodeDataHead );

void displayMetaDataError( int code );

OpCodeType *clearMetaDataList( OpCodeType *localPtr );
