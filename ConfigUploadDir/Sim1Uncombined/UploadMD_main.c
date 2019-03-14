#include <stdio.h>
#include "MetaDataAccess.h"

int main( int argc, char **argv )
   {
      int mdAccessResult;
      char mdFileName[ MAX_STR_LEN ];
      OpCodeType *mdData;

      printf( "\nMeta Data File Upload Program\n" );
      printf( "=============================\n" );

      if( argc < 2 )
         {
            printf( "\nERROR: Program requires file name for meta data file" );
            printf( "as command line arguement\n" );
            printf( "Program terminated\n" );

            return 1;
			}

      copyString( mdFileName, argv[ 1 ] );
      mdAccessResult = getOpCodes( mdFileName, &mdData );

      if( mdAccessResult == NO_ERR )
         {
            displayMetaData( mdData );
         }
      else
         {
            displayMetaDataError( mdAccessResult );				
         }

         mdData = clearMetaDataList( mdData );
         printf("\n");

         return 0;   
   }