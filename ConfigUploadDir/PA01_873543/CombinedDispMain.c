#include <stdio.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"

int main( int argc, char ** argv )
	{
		int configAccessResult, mdAccessResult;
		char configFileName[ MAX_STR_LEN ];
		char mdFileName[ MAX_STR_LEN ];
		ConfigDataType *configDataPtr;
		OpCodeType *mdData;
            
        //display title
            //function: printf
        printf( "\nConfig File Upload Program\n" );
        printf( "==========================\n\n" );

        //check for not correct number of command line arguments (two)
        if( argc < 2 )
            {
                //print missing command line argument error
                    //function: printf
                printf ( "ERROR: Program requires file name for config file " );
                printf ( "as command line argument\n" );
                printf ( "Program Terminated\n" );

                //return non-normal program result (anything other than 0)
                return 1;
            }
        
        //get data from configuration file
            //function: copyString, getConfigData
        copyString( configFileName, argv[ 1 ] );
        configAccessResult = getConfigData( configFileName, &configDataPtr);

        //check for succeful upload
        if( configAccessResult == NO_ERR )
            {
                //display config file
                    //function: displayConfigData
                displayConfigData( configDataPtr );                  
            }

        //otherwise, assume failed upload
        else
            {
                 //display configuration upload error
                //function: displayConfigError
                displayConfigError( configAccessResult );
            }




 		printf( "\nMeta Data File Upload Program\n" );
      printf( "=============================\n" );

      if( argc < 2 )
         {
            printf( "\nERROR: Program requires file name for meta data file" );
            printf( "as command line arguement\n" );
            printf( "Program terminated\n" );

            return 1;
			}

      copyString( mdFileName, configDataPtr->metaDataFileName );
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
        
        //shut down program

            //clear configuration data
                //function: clearConfigData
            clearConfigData( &configDataPtr );


            //add endline vertical spacing
                //function: printf
            printf( "\n" );

            //return program success
        return 0;
    }
