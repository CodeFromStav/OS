#include <stdio.h>
#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"

int main( int argc, char ** argv )
	{
        char *timeStr = (char *) malloc( MAX_STR_LEN );
		int configAccessResult, mdAccessResult;
		char configFileName[ MAX_STR_LEN ];
		char mdFileName[ MAX_STR_LEN ];
		ConfigDataType *configDataPtr;
		OpCodeType *metaDataPtr;
        //PCB_LL *currentNodePtr;
/*
        char *timeStr = (char *) malloc(MAX_STR_LEN );
        char *displayString = (char *) malloc(MAX_STR_LEN );
        char *messageStr = (char *) malloc(MAX_STR_LEN );

  */      
        // if( currentNodePtr->MonitorFlag == True )
        //     {
        //         printf( "\nSimulator Program\n"  );
        //         printf( "==================\n\n" );
        //         printf( "Uploading Configuration Files\n\n" );
        //         printf( "Uploading Meta Data Files\n\n" );
        //         printf( "=================\n" );
        //         printf( "Begin Simulation\n\n" );
        //     }



		// logSettings output;

		// output.printToMonitor == True;
		// output.printToLog == True;
		// output.logFile = ".log";

		// startLogging( &output );
        // LOGTO_MONITOR_CODE,
           //    LOGTO_FILE_CODE,
             //  LOGTO_BOTH_CODE

        // if( LOGTO_FILE_CODE || LOGTO_BOTH_CODE )
        //     {
        //         currentNodePtr->LogFlag == True;
        //     }
        
        // else if( LOGTO_MONITOR_CODE || LOGTO_BOTH_CODE )
        //     {
        //          currentNodePtr->MonitorFlag == True;
        //     }

        // if( LogFlag )
        //     {
        //         //print to file
        //     }
        // else if( MonitorFlag )
        //     {
        //         //print to monitor
        //     }

         
        printf( "\nSimulator Program" );
        printf( "\n=================\n" );		  
        printf( "\nUploading Configuration Files\n" );
        printf( "\nUploading Meta Data Files" );
        printf( "\n==================" );
        printf( "\nBegin Simulation\n" );

        // runTimer( 0 ); //start timer

        


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
               simRun( configDataPtr, metaDataPtr, timeStr );      
               // displayConfigData( configDataPtr );      
    
            }

        else
            {
                displayConfigError( configAccessResult );
            }


      if( argc < 2 )
         {
            printf( "\nERROR: Program requires file name for meta data file" );
            printf( "as command line arguement\n" );
            printf( "Program terminated\n" );

            return 1;
			}

      copyString( mdFileName, configDataPtr->metaDataFileName );
      mdAccessResult = getOpCodes( mdFileName, &metaDataPtr ); //accesses the opCodes

    //   if( mdAccessResult == NO_ERR ) //runs the simulation
    //      {
    //         simRun(configDataPtr, metaDataPtr, timeStr ); //this runs the simulation      
    //         //displayMetaData( metaDataPtr );      
    //      }
    //   else
    //      {
    //         displayMetaDataError( mdAccessResult );				
    //      }

         	metaDataPtr = clearMetaDataList( metaDataPtr );
        
            clearConfigData( &configDataPtr );

            printf( "\n" );

			// stopLogging();

            free( timeStr );

        return 0;
    }
