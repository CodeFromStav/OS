#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include "threadManager.h"
#include <pthread.h>


void *threadEntry( void *param)
{
   int *intparam = (int *)param;
   runTimer( *intparam ); //might be &param
   return NULL;
}

//sleeper
void threadSleeper ( int timeToWait, char *timeStr )
{
   double toTime, tempDouble;
   char *tempStr  = (char *) malloc(MAX_STR_LEN );

   //get miliseconds in proper format (i.e. 
   double waitTime = timeToWait / 100;
   // this is to make sure the math is correct (both numbers will be the same 
   // length
   waitTime += 0.000000;
   sscanf(timeStr, "%lf", &toTime);
   toTime += waitTime;

   while (tempDouble < toTime )
   {
      // keeps going until timer is equal to or greater than timer
      accessTimer( LAP_TIMER, tempStr ); 
      sscanf(timeStr, "%lf", &tempDouble);
   }

   free( tempStr );
}

PCB_LL *createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr )
{
   PCB_LL *headNodePtr = NULL;
   PCB_LL *currentNodePtr = NULL;
   OpCodeType *tempPtr = currentPtr;


   // accessTimer( LAP_TIMER, timeStr ); //possibly initialize timeStr
   // printf("%s, OS: Create Process Control Blocks \n", timeStr );


   headNodePtr = malloc( sizeof( PCB_LL ) );

   int processNum = 0;

   headNodePtr->progCounter = tempPtr;
   headNodePtr->stateOfProcess = NEW;
   headNodePtr->PID = processNum;
   headNodePtr->timeRemaining = calcRemainingTime( tempPtr, configPtr );
   headNodePtr->next = NULL;


   //S will always be the first OP, so move 1 to the right
   tempPtr = tempPtr->next; //moves one to the right since S will always be at the beginning
   //Set the head = to the safetyPointer
  // tailNodePtr = headNodePtr;
   currentNodePtr = headNodePtr;

   while( tempPtr != NULL )  //might be ->next
   {
      //if the process is A, and its a start, then make a new PCB
      if( tempPtr->opLtr == 'A' 
             && (compareString( tempPtr->opName, "start" ) == 0 ) )
         {
            currentNodePtr = currentNodePtr->next; //sets current Ptr
            currentNodePtr = malloc( sizeof( PCB_LL ) ); //creates the next Process Node
            currentNodePtr->stateOfProcess = NEW;
            processNum++;
            accessTimer( LAP_TIMER, timeStr ); //lap now PCB has been created.
         }

      tempPtr = tempPtr->next;

   }
   
   free( headNodePtr );
   free( currentNodePtr );

   return headNodePtr;

 

}
 
void simRun( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr )
{
   
   PCB_LL *localNodePtr = malloc( sizeof( PCB_LL ) );
   //PCB_LL *headNodePtr = localNodePtr; //placeholder
   int timeRemaining = 0;
   int CycleRate = configPtr->ioCycleRate;
   int CurrentVal = localNodePtr->progCounter->opValue;

   // localPtr = malloc( sizeof( PCB_LL ) );
   
  // localNodePtr = localPtr;

   while( localNodePtr != NULL ) //OUTER PCB LOOP
      {
         accessTimer( ZERO_TIMER, timeStr);
         printf( "%s, OS: System Start\n", timeStr );

         accessTimer( LAP_TIMER, timeStr );
         printf( "%s, OS: Create Process Control Blocks\n", timeStr );
         createPCB( configPtr, currentPtr, timeStr );

         accessTimer( LAP_TIMER, timeStr );
         printf( "%s, OS: All processes initialized in New state\n", timeStr ); //done in createPCB

         accessTimer( LAP_TIMER, timeStr );
         printf( "%s, OS: All processes now set in Ready state\n", timeStr );

         // while( localNodePtr != NULL )
         //    {
         //       localNodePtr->stateOfProcess = READY;
         //       localNodePtr = localNodePtr->next;
         //    }
        // localNodePtr = headNodePtr;//reset to first process.

        //timeRemaining = calcRemainingTime( currentPtr, configPtr );

         accessTimer( LAP_TIMER, timeStr );
         printf( "%s, OS: Process %d selected with %d ms remaining\n", timeStr, localNodePtr->PID, timeRemaining );

         accessTimer( LAP_TIMER, timeStr );
         printf( "%s, OS: Process %d set in RUNNING state\n\n", timeStr, localNodePtr->PID );

         //set to state
         //localNodePtr->progCounter = localNodePtr->progCounter->next;

//start of main loop
         while( (  localNodePtr->progCounter->next->opLtr != 'A' )
             && ( compareString( localNodePtr->progCounter->opName, "end" ) != 0 ) ) //INNER PROG COUNTER
         {
            printf("asfsafsafsa");
            outputProc( configPtr, currentPtr, timeStr ); //outputs based on opLtr
            printf("1234");


            if ( localNodePtr->progCounter->opLtr == 'P' )//P
            {
               runTimer( localNodePtr->progCounter->opValue * configPtr->procCycleRate );
            }

            else if( localNodePtr->progCounter->opLtr == 'I' ||
                        localNodePtr->progCounter->opLtr == 'O' ) //I/O
            {
               pthread_t thread0;
               int runTime = CycleRate * CurrentVal;
               pthread_create( &thread0, NULL, threadEntry, &runTime);
               pthread_join( thread0, NULL );
            }
            // else //M
            // {
               
            // }
            
            localNodePtr->progCounter = localNodePtr->progCounter->next;
         }

         localNodePtr = localNodePtr->next;

      }   

      free( localNodePtr );

}

/*
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
*/


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

void createDisplayString( char *displayString, char *timeString, char *messageStr )
{
   concatenateString( displayString, timeString );
   concatenateString( displayString, messageStr );
}

//function to display based on flags passed in

void displayLoc( Boolean monitorFlag, Boolean fileFlag, char *str, ConfigDataType *configPtr )
{
   FILE *fptr = fopen( configPtr->logToFileName, "w" );

    if( monitorFlag )
    {
       printf( "%s", str );
    }
    if( fileFlag )
    {
      fprintf( fptr,"%s", str );
    }
}

void outputProc( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr )
{
   //char *timeStr[MAX_STR_LEN];
   PCB_LL *pcbPtr = malloc( sizeof( PCB_LL ) );
   timeStr = (char *) malloc( MAX_STR_LEN );
   char* displayStr = (char *) malloc( MAX_STR_LEN );
   char *messageStr = (char *) malloc( MAX_STR_LEN );
   char operatingChar = currentPtr->opLtr;
   
   //displayStr = (", Process: %d ", pcbPtr->PID);  
   displayStr = ", Process: 0, " ;

   switch( operatingChar )
   {
      case 'A':
         // Program application used with Start and End
         if( compareString( currentPtr->opName, "start") == 0 )
         {
            messageStr = "run operation start\n";
         }
         else if( compareString( currentPtr->opName, "end" ) == 0 )
         {
            messageStr = "run operation end\n";
         }
         accessTimer( LAP_TIMER, timeStr ); 
         createDisplayString( displayStr, timeStr, messageStr );
         displayLoc( pcbPtr->MonitorFlag, pcbPtr->LogFlag, displayStr, configPtr );

      break;

      case 'I':

         messageStr = currentPtr->opName;
         concatenateString( messageStr, " input start\n" );
         accessTimer( LAP_TIMER, timeStr ); 
         createDisplayString( displayStr, timeStr, messageStr );
         displayLoc( pcbPtr->MonitorFlag, pcbPtr->LogFlag, displayStr, configPtr );

         //sleep for amount of time specified
         threadSleeper( currentPtr->opValue, timeStr );

         messageStr = currentPtr->opName;
         concatenateString( messageStr, " input end\n" );
         accessTimer( LAP_TIMER, timeStr ); 
         createDisplayString( displayStr, timeStr, messageStr );
         displayLoc( pcbPtr->MonitorFlag, pcbPtr->LogFlag, displayStr, configPtr );

      break;

      case 'O':
         // Output used with descriptors
         messageStr = currentPtr->opName;
         concatenateString( messageStr, " output start\n" );
         accessTimer( LAP_TIMER, timeStr ); 
         createDisplayString( displayStr, timeStr, messageStr );
         displayLoc( pcbPtr->MonitorFlag, pcbPtr->LogFlag, displayStr, configPtr );

         //sleep for amount of time specified
         threadSleeper( currentPtr->opValue, timeStr );
         
         messageStr = currentPtr->opName;
         concatenateString( messageStr, " output end\n" );
         accessTimer( LAP_TIMER, timeStr ); 
         createDisplayString( displayStr, timeStr, messageStr );
         displayLoc( pcbPtr->MonitorFlag, pcbPtr->LogFlag, displayStr, configPtr );

      break;
   }
   free( pcbPtr );
   free( timeStr );
   free( displayStr );
   free( messageStr );

}


   
