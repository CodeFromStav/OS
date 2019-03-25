#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include "threadManager.h"
#include <pthread.h>




//function to create the string output to either the file or the user
void createDisplayString( char *displayString, char *timeString, char *messageStr )
{
   concatenateString( displayString, timeString );
   concatenateString( displayString, messageStr );
}

//function to display based on flags passed in
void display( Boolean monitorFlag, Boolean fileFlag, char *str ,
              char **fileBuffer, int currentIndex)
{
    if( monitorFlag == True )
    {
       printf( "%s", str );
    }
    if( fileFlag == True )
    {
      fileBuffer[ currentIndex ] = str;
    }
}

void simRun(  ConfigDataType *configPtr, OpCodeType *currentPtr )
{
	Boolean endOfProgram = False;
   int timeRemaining;
	//int size;
	//int tempInt;
   ProgRun *pcb;
   //char *fileName = (char *) malloc(MAX_STR_LEN );
   char *timeStr = (char *) malloc(MAX_STR_LEN );
   char *displayString = (char *) malloc(MAX_STR_LEN );
   char *messageStr = (char *) malloc(MAX_STR_LEN );
   char *tempStr = (char *) malloc(MAX_STR_LEN );
   pthread_t thread0;

	//PCB_LL ProcessControl;


 	displayString = "   ";
   accessTimer( ZERO_TIMER, timeStr ); 
   messageStr = ", OS: System Start\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayString = "   ";
   accessTimer( LAP_TIMER, timeStr ); 
   messageStr = ", OS: Create Process Control Blocks\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayString = "   ";
   accessTimer( LAP_TIMER, timeStr ); 
   messageStr = ", OS: All processes initialized in New state\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayString = "   ";
   accessTimer( LAP_TIMER, timeStr ); 
   messageStr = ", OS: All processes now set in Ready state\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;


	displayString = "   ";
   accessTimer( LAP_TIMER, timeStr );

	timeRemaining = calcRemainingTime( currentPtr, configPtr );

	// sprintf converts a int into string which is placed in tempStr 
   // (this is part of <stdio.h>)
   messageStr = ", OS: Process 0 selected with ";

   sprintf( tempStr, "%d", timeRemaining);
   concatenateString(messageStr , tempStr);

   tempStr = " ms remaining\n";
   concatenateString(messageStr, tempStr);

   // merge strings and print
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

	 //start program

   // we are using currentPtr to progress through the list
   //Set processes to Running state
   displayString = "   ";
   accessTimer( LAP_TIMER, timeStr ); 
   messageStr = ", OS: Process 0 set in RUNNING state\n\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //move temp pointer to first operation
   currentPtr = currentPtr->next;
   while( endOfProgram != True )
   {
     // create thread
     pthread_create( &thread0, NULL, threadEntry, &pcb);
     // wait for thread to complete
     pthread_join( thread0, NULL );
     // move pointer to next program
     currentPtr = currentPtr->next;
     // The only 'S' found in the loop is S( end )
     if( currentPtr->opLtr == 'S' )
       {
          endOfProgram = True;
       }
   }  

	// display end of flag
   displayString = "\n"; 
   display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;
   
   //end program
   displayString = "   ";
   accessTimer( LAP_TIMER, timeStr ); 
   messageStr = ", OS: Process 0 ended and set in EXIT state\n\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //stop system
   displayString = "   ";
   accessTimer( STOP_TIMER, timeStr ); 
   messageStr = ", OS: System Stop\n\n";
   createDisplayString( displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

	// print the final monitor output
   if( pcb->monitorFlag )
   {
      printf("End Simulation - Complete\n");
      printf("=========================\n\n");
   }
   // dump log to file
   logDump( pcb );
   // free memory
  // clearUploadData
   free( displayString );
   free( timeStr );
   //free( fileName );
   free( messageStr );
   free( tempStr );
}


//function to print all required output to the log file
void logDump( ProgRun *pcb)
{
   char *tempStr = (char *) malloc(MAX_STR_LEN );
   char *anotherTempStr = (char *) malloc(MAX_STR_LEN );
   char *fileName = (char *) malloc(MAX_STR_LEN );
   ConfigDataType *tempConfigPtr = pcb->accessPtr;
   int index = 0;

   // open file 'w' clears the file for a new dump
   fileName = tempConfigPtr->logToFileName;
	FILE *filePtr = fopen( fileName, "w" );
   // begin file write
   fprintf(filePtr, "==================================================\n");
   fprintf(filePtr, "Simulator Log File Header\n\n");

   // concatenate meta filename and newline
   // reusing filename so less memory is used, the pointer is all I need
   fileName = tempConfigPtr->metaDataFileName;
   tempStr = "File Name                       : ";
   concatenateString( tempStr, fileName );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // scheduling doesn't change
   fprintf(filePtr, "CPU Scheduling                  : FCFS-N\n");

   // print quant cycles
   tempStr ="Quantum Cycles                  : ";
   sprintf( anotherTempStr, "%d", tempConfigPtr->quantumCycles);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // print mem available
   tempStr ="Memory Available (KB)           : ";
   sprintf( anotherTempStr, "%d", tempConfigPtr->memAvailable);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // print processor cycle rate
   tempStr = "Processor Cycle Rate (ms/cycle) : ";
   sprintf( anotherTempStr, "%d", tempConfigPtr->procCycleRate);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // print I/O cycle rate
   tempStr ="I/O Cycle Rate (ms/cycle)       : ";
   sprintf( anotherTempStr, "%d", tempConfigPtr->ioCycleRate);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   //print the excess
   fprintf(filePtr, "================\n");
   fprintf(filePtr, "Begin Simulation\n\n");
   
   //loop through buffer and print it
   while( index < pcb->currentIndex )
   {
      tempStr = pcb->fileBuffer[index];
      fprintf( filePtr, "%s", tempStr );
      index++;
   }
   
   //print end bit
   fprintf(filePtr, "End Simulation - Complete\n");
   fprintf(filePtr, "=========================\n\n");
   fclose( filePtr );
   //free data
   free( tempStr );
   free(anotherTempStr);
   free( fileName );

}



// void ProcessType ( ConfigDataType *configPtr, OpCodeType *currentPtr )
// 	{
// 		char timeString[ MAX_STR_LEN ];
// 		States stateOfProcess;
// 		OpCodeType *LL_tailNodePtr; //tail of metaData LL

// 		while( currentPtr != NULL ) 
// 			{
// 				if( currentPtr->opLtr == 'A' ) //can either be (start) or (end)
// 					{
// 						stateOfProcess = NEW;
// 						printf( "%d ", stateOfProcess  );
// 					}
// 				else if( currentPtr->opLtr == 'P' ) //(run)
// 					{
// 						  stateOfProcess = RUNNING;
// 						  printf( "%d ", stateOfProcess );
// 					}
// 				else if( currentPtr->opLtr == 'I' ) //can be (keyboard) or (hard drive)
// 					{
// 						  stateOfProcess = RUNNING;
// 						  printf("%d ", stateOfProcess );
// 					}
// 				else if( currentPtr->opLtr == 'O' ) //can either be (printer)
// 					{
// 						  stateOfProcess = RUNNING;
// 						  printf( "%d ", stateOfProcess );
// 					}
// 				else //Ltr 'S' can either be (start) or (end)
// 					{		
// 						accessTimer( ZERO_TIMER, timeString );
// 						printf( "%s, OS: System Start", timeString );

// 						LL_tailNodePtr = LL_tailNodePtr->next;
// 						LL_tailNodePtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

// 						currentPtr = currentPtr->next;
// 						currentPtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

// 					}
// 			}
// 	}

int calcRemainingTime( OpCodeType *currentPtr , ConfigDataType *configPtr )
	{
		int opCodeValue = currentPtr->opValue;
		double remainingTime = 0.0;
		int procCycleRate = configPtr->procCycleRate;
		int ioCycleRate = configPtr->ioCycleRate;

		while( currentPtr != NULL )
			{

				if ( currentPtr->opLtr == 'P' )
					{
						remainingTime += ( opCodeValue * procCycleRate ); 
					}

				else // 'I/O'
					{
						remainingTime += ( opCodeValue * ioCycleRate );
					}

				currentPtr = currentPtr->next;
			}

		return remainingTime;		
	}
