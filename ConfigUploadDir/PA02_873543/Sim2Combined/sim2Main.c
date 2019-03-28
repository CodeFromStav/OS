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
		OpCodeType *metaDataPtr;
        PCB_LL *currentNodePtr;

        char *timeStr = (char *) malloc(MAX_STR_LEN );
        char *displayString = (char *) malloc(MAX_STR_LEN );
        char *messageStr = (char *) malloc(MAX_STR_LEN );

        
        if( localNodePtr->MonitorFlag == True )
            {
                printf( "\nSimulator Program\n"  );
                printf( "==================\n\n" );
                printf( "Uploading Configuration Files\n\n" );
                printf( "Uploading Meta Data Files\n\n" );
                printf( "=================\n" );
                printf( "Begin Simulation\n\n" );
            }

        displayString = "   ";
        accessTimer( ZERO_TIMER, timeStr ); 
        messageStr = ", OS: System Start\n";
        createDisplayString( displayString, timeStr, messageStr );
        display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->currentIndex );
        //pcb->currentIndex++;



        displayString = "   ";
        accessTimer( LAP_TIMER, timeStr ); 
        messageStr = ", OS: Create Process Control Blocks\n";
        createDisplayString( displayString, timeStr, messageStr );
        display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->currentIndex );
       // pcb->currentIndex++;



        displayString = "   ";
        accessTimer( LAP_TIMER, timeStr ); 
        messageStr = ", OS: All processes initialized in New state\n";
        createDisplayString( displayString, timeStr, messageStr );
        display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->currentIndex );
        //pcb->currentIndex++;



        displayString = "   ";
        accessTimer( LAP_TIMER, timeStr ); 
        messageStr = ", OS: All processes now set in Ready state\n";
        createDisplayString( displayString, timeStr, messageStr );
        display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->currentIndex );
       // pcb->currentIndex++;


        displayString = "   ";
        accessTimer( LAP_TIMER, timeStr );

        timeRemaining = calcRemainingTime( currentPtr, configPtr );

        // sprintf converts a int into string which is placed in tempStr 
        // (this is part of <stdio.h>)
        messageStr = ", OS: Process %s selected with ", currentNodePtr->progCounter ;

        sprintf( tempStr, "%d", timeRemaining);
        concatenateString(messageStr , tempStr);

        tempStr = " ms remaining\n";
        concatenateString(messageStr, tempStr);

        // merge strings and print
        createDisplayString( displayString, timeStr, messageStr );
        display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
                    pcb->currentIndex );
        pcb->currentIndex++;

    //build linked list of PCB pointing to metaData


    



		// logSettings output;

		// output.printToMonitor == True;
		// output.printToLog == True;
		// output.logFile = ".log";

		// startLogging( &output );

        if( compareString(configDataPtr->logToCode, "Both" ) == 0 || compareString( configDataPtr->logToCode = "File" ) )
            {
                LogFlag == True;
            }
        
        else if( compareString( configDataPtr->logToCode, "Both" || "Monitor" ) )
            {
                MonitorFlag == True;
            }

        if( LogFlag )
            {
                //print to file
            }
        else if( MonitorFlag )
            {
                //print to monitor
            }

         
        printf( "\nSimulator Program" );
        printf( "\n=================\n" );		  
        printf( "\nUploading Configuration Files\n" );
        printf( "\nUploading Meta Data Files" );
        printf( "\n==================" );
        printf( "\nBegin Simulation\n" );

        runTimer( 0 ); //start timer


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
                simRun( configDataPtr, metaDataPtr );          
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

      if( mdAccessResult == NO_ERR ) //runs the simulation
         {
            simRun(configDataPtr, metaDataPtr ); //this runs the simulation      
            //displayMetaData( metaDataPtr );      
         }
      else
         {
            displayMetaDataError( mdAccessResult );				
         }

         	metaDataPtr = clearMetaDataList( metaDataPtr );
        
            clearConfigData( &configDataPtr );

            printf( "\n" );

			// stopLogging();

        return 0;
    }
