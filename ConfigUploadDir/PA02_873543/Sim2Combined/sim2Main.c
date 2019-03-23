#include <stdio.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include "log.h"

int main( int argc, char ** argv )
	{

		int configAccessResult, mdAccessResult;
		char configFileName[ MAX_STR_LEN ];
		char mdFileName[ MAX_STR_LEN ];
		ConfigDataType *configDataPtr;
		OpCodeType *mdData;

		// logSettings output;

		// output.printToMonitor == True;
		// output.printToLog == True;
		// output.logFile = ".log";

		// startLogging( &output );


            
         
        printf( "\nSimulator Program" );
        printf( "\n=================\n" );		  
        printf( "\nUploading Configuration Files\n" );
        printf( "\nUploading Meta Data Files" );
        printf( "\n==================" );
        printf( "\nBegin Simulation\n" );


        if( argc < 2 )
            {
                printf ( "ERROR: Program requires file name for config file " );
                printf ( "as command line argument\n" );
                printf ( "Program Terminated\n" );

                return 1;
            }
        
        copyString( configFileName, argv[ 1 ] );
        configAccessResult = getConfigData( configFileName, &configDataPtr);

        if( configAccessResult == NO_ERR )
            {
                displayConfigData( configDataPtr );                  
            }

        else
            {
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
      mdAccessResult = getOpCodes( mdFileName, &mdData ); //accesses the opCodes

      if( mdAccessResult == NO_ERR ) //runs the simulation
         {
            simRun(configDataPtr, mdData ); //this runs the simulation      
            //displayMetaData( mdData );      
         }
      else
         {
            displayMetaDataError( mdAccessResult );				
         }

         	mdData = clearMetaDataList( mdData );
        
            clearConfigData( &configDataPtr );

            printf( "\n" );

			// stopLogging();

        return 0;
    }
