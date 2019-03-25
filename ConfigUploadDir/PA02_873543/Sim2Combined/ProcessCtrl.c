#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include "threadManager.h"
//#include <pthread.h>




//function to create the string output to either the file or the user
void createDisplayStr ( char *displayStr, char *timeStr, char *messageStr )
{
   concatenateString( displayString, timeString );
   concatenateString( displayString, tempStr );
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
	char *displayString = (char *) malloc(MAX_STR_LENGTH);
	char *timeStr = (char *) malloc(MAX_STR_LENGTH);
	char *messageStr = (char *) malloc(MAX_STR_LENGTH);

	Boolean endOfProgram = False;


	ProgRun *pcb;
	int timeRemaining;
	OpCodeType *tempPtr;
   pthread_t thread0;
	
	Boolean endOfProgram = False;
   int size, timeLeft, tempInt;
   OpCode *tempPtr;
   ProcessControlBlock *pcb;
   char *fileName = (char *) malloc(MAX_STR_LENGTH);
   char *timeStr = (char *) malloc(MAX_STR_LENGTH);
   char *displayString = (char *) malloc(MAX_STR_LENGTH);
   char *messageStr = (char *) malloc(MAX_STR_LENGTH);
   char *tempStr = (char *) malloc(MAX_STR_LENGTH);
   pthread_t thread0;





	//PCB_LL ProcessControl;


 	displayStr = "   ";
   accessTimer( ZERO_TIMER, &timeStr ); 
   messageStr = ", OS: System Start\n";
   createDisplayStr ( &displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr ); 
   messageStr = ", OS: Create Process Control Blocks\n";
   createDisplayStr ( &displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr ); 
   messageStr = ", OS: All processes initialized in New state\n";
   createDisplayStr ( &displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;



 	displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr ); 
   messageStr = ", OS: All processes now set in Ready state\n";
   createDisplayStr ( &displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString ,
				 pcb->fileBuffer, pcb->currentIndex );
   pcb->currentIndex++;


	displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr );

	timeRemaining = calcRemainingTime( currentPtr, configPtr );

	// sprintf converts a int into string which is placed in tempStr 
   // (this is part of <stdio.h>)
   messageStr = ", OS: Process 0 selected with ";

   sprintf( tempStr, "%d", timeRemaining);
   concatenateString(messageStr , tempStr);

   tempStr = " ms remaining\n";
   concatenateString(messageString, tempStr);

   // merge strings and print
   createDisplayStr ( &displayString, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

	 //start program

   // we are using tempPtr to progress through the list
   //Set processes to Running state
   displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr ); 
   messageStr = ", OS: Process 0 set in RUNNING state\n\n";
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //move temp pointer to first operation
   tempPtr = tempPtr->next
   while( endOfProgram != True )
   {
     // create thread
     pthread_create( &thread0, NULL, threadEntry, &pcb);
     // wait for thread to complete
     pthread_join( thread0, NULL );
     // move pointer to next program
     tempPtr = tempPtr->next;
     // The only 'S' found in the loop is S( end )
     if( tempPtr->opLtr == 'S' )
       {
          endOfProgram = True;
       }
   }  

	// display end of flag
   displayStr = "\n"; 
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;
   
   //end program
   displayStr = "   ";
   accessTimer( LAP_TIMER, &timeStr ); 
   messageStr = ", OS: Process 0 ended and set in EXIT state\n\n";
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //stop system
   displayStr = "   ";
   accessTimer( STOP_TIMER, &timeStr ); 
   messageStr = ", OS: System Stop\n\n";
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
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
   clearUploadData
   free( displayString );
   free( timeString );
   //free( fileName );
   free( messageStr );
   free( tempStr );
}


//function to print all required output to the log file
void logDump( ProgRun *pcb);
{
   char *tempStr = (char *) malloc(MAX_STR_LENGTH);
   char *anotherTempStr = (char *) malloc(MAX_STR_LENGTH);
   char *fileName = (char *) malloc(MAX_STR_LENGTH);
   ConfigDataType *tempConfigPtr = pcb->accessPtr;
   int index = 0;

   // open file 'w' clears the file for a new dump
   fileName = tempConfigPtr->logToFileName;
   File *filePtr = freopen( fileName, 'w' );

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
   tempStr ="Memory Available (KB)           : ");
   sprintf( anotherTempStr, "%d", tempConfigPtr->memAvailable);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // print processor cycle rate
   tempStr = "Processor Cycle Rate (ms/cycle) : ");
   sprintf( anotherTempStr, "%d", tempConfigPtr->procCycleRate);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   // print I/O cycle rate
   tempStr ="I/O Cycle Rate (ms/cycle)       : ");
   sprintf( anotherTempStr, "%d", tempConfigPtr->ioCycleRate);
   concatenateString( tempStr, anotherTempStr );
   concatenateString( tempStr, "\n" );
   fprintf( filePtr, "%s", tempStr );

   //print the excess
   fprintf("================\n");
   fprintf("Begin Simulation\n\n");
   
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





// 	printf( "\nSystem Start");
// 	//access at 0 timer
// 	accessTimer( ZERO_TIMER, timeString );
// 	//possibly a timeToString call
// 	//void timeToString( int secTime, int uSecTime, char *timeStr )
// 	//timeToString( , , timeString );

// 	printf( "\nCreating Process Control Blocks");
// 	//call function to create PCB
// 	//PCB_LL *LinkedList = createPCB( configPtr, currentPtr ); //function needs to create PCBS
// 	createPCB( configPtr, currentPtr );
// 	//access timer LAP
// 	accessTimer( LAP_TIMER, timeString );

	

// //all processes initialized in new state

// 	//for loop setting new process states to NEW
// 	while( currentPtr != NULL )
// 		{
// 			//ProcessControl->
// 			currentPtr = currentPtr->next;
// 		}

// 	printf( "\nAll processes initilized in " );
// 	//printf( "%s", LinkedList->stateOfProcess );
// 	printf( " state");


// 	//ACCESS TIMER LAP
// 	accessTimer( LAP_TIMER, timeString );

// //all processes initialized in ready state

// 	//run loop to set in READY state
// 	while( currentPtr != NULL )
// 		{
// 		//	LinkedList->stateOfProcess = READY;
// 			currentPtr = currentPtr->next;
// 		}

// 	printf( "\nAll processes now set in " );
// 	//printf( "%s", LinkedList->stateOfProcess );
// 	printf( " state");

// 	//ACCESS LAP TIMER
// 	accessTimer( LAP_TIMER, timeString );

// 	//"Process" + PID + "se;ected with" + RemainingTime + "ms remaining"
// 	printf( "\n Process " );
// //	printf( "%s", LinkedList->PID );
// 	printf( " selected with ");
// //	printf( "%d" , LinkedList->timeRemaining );
// 	printf( " ms remaining\n" );

// 	//ACCESS LAP TIMER
// 	accessTimer( LAP_TIMER, timeString );


// 	//set Process 0 to running state
// 	//LinkedList->stateOfProcess = RUNNING;

// 	//"Process" + PID + "set in " + stateOfOperation + "state"
// 	printf( "\n Process " );
// //	printf( "%s", LinkedList->PID );
// 	printf( " set in ");
// //	printf( "%d" , LinkedList->stateOfProcess );
// 	printf( " state" );

// 	//ACCESS LAP TIMER
// 	accessTimer( LAP_TIMER, timeString );



// 	//loop

// }



//

// PCB_LL *createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr )
// 	{
// 		PCB_LL *PCB_LocalPtr;
// 		int PID = 0;
// 		double timeRemaining = calcRemainingTime( currentPtr, configPtr );
// 		States stateOfProcess = NEW;
	
// 	}

// PCB_LL createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr )
// 	{
// 		if( currentPtr == NULL )
// 			{
// 				PCB_LL *localPtr =  malloc ( sizeof ( PCB_LL ) ); //neeed to point to opCodeType
// 				localPtr->next = NULL;
// 				PCB_LL *headPtr = localPtr;
// 				PCB_LL *tailPtr = headPtr;

// 				localPtr->PID = 0;
// 				localPtr->stateOfProcess = NEW;
// 				localPtr->timeRemaining = calcRemainingTime( currentPtr, configPtr );
// 				localPtr->next = malloc( sizeof( PCB_LL ) );
// 			}
		


		// if( localPtr->next == NULL )
		// 	{
		// 		localPtr->next = malloc ( sizeof ( PCB_LL ) );



		// 	}
		// while( localPtr->next != NULL )
		// 	{

		// 	}


/*int PID;
		double timeRemaining;
		States stateOfProcess;
	

		
		struct PCB_LL * next;
*/
		
	//}

void ProcessType ( ConfigDataType *configPtr, OpCodeType *currentPtr )
	{
		char timeString[ MAX_STR_LEN ];
		States stateOfProcess;
		OpCodeType *LL_tailNodePtr; //tail of metaData LL

		while( currentPtr != NULL ) 
			{
				if( currentPtr->opLtr == 'A' ) //can either be (start) or (end)
					{
						stateOfProcess = NEW;
						printf( "%d ", stateOfProcess  );
					}
				else if( currentPtr->opLtr == 'P' ) //(run)
					{
						  stateOfProcess = RUNNING;
						  printf( "%d ", stateOfProcess );
					}
				else if( currentPtr->opLtr == 'I' ) //can be (keyboard) or (hard drive)
					{
						  stateOfProcess = RUNNING;
						  printf("%d ", stateOfProcess );
					}
				else if( currentPtr->opLtr == 'O' ) //can either be (printer)
					{
						  stateOfProcess = RUNNING;
						  printf( "%d ", stateOfProcess );
					}
				else //Ltr 'S' can either be (start) or (end)
					{		
						accessTimer( ZERO_TIMER, timeString );
						printf( "%s, OS: System Start", timeString );

						LL_tailNodePtr = LL_tailNodePtr->next;
						LL_tailNodePtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

						currentPtr = currentPtr->next;
						currentPtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

					}
			}
	}

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







	/*
		OpCodeType *LL_headNodePtr = NULL; //head of metaData LL
	OpCodeType *LL_tailNodePtr = NULL; //tail of metaData LL

	PCB_LL *localNodePtr = NULL; //PCB LL current node
	PCB_LL *headLocalNodePtr = NULL;


	char timeString[ MAX_STR_LEN ];
	int remainingTime = calcFinalTime( currentPtr, configPtr );
	OpCodeType *endCheck = currentPtr->next->next;

	LL_headNodePtr = ( OpCodeType * ) malloc ( sizeof( OpCodeType ) );
	LL_tailNodePtr = LL_headNodePtr;
	currentPtr = headLocalNodePtr;
	
	PCB_LL *pcb_LocalPtr = createPCB( configPtr, currentPtr );

	 while( endCheck != NULL ) //checks if at final A(end)
	 	{
			ProcessType( configPtr, currentPtr );
		
			while( compareString( currentPtr->opName, "end") != 0 ) //checks when A(start) -> A(end) finished, then increments to next process
				{	
				
				currentPtr = currentPtr->next;
				currentPtr = ( OpCodeType * ) malloc ( sizeof( OpCodeType ) );

				}			
				
				pcb_LocalPtr = pcb_LocalPtr->next;
				pcb_LocalPtr = ( PCB_LL * ) malloc ( sizeof ( PCB_LL ) );
				pcb_LocalPtr->PID++;
			}

		LL_tailNodePtr = currentPtr; //sets the tail as A(end)
		*/
	