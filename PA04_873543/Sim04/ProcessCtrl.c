#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include "threadManager.h"
#include <pthread.h>


void *threadEntry( void *param)
{
   int *intparam = (int *)param;
   runTimer( *intparam );
   return NULL;
}

void threadSleeper ( int timeToWait, char *timeStr )
{
   double toTime, tempDouble;
   char *tempStr  = (char *) malloc(MAX_STR_LEN );
   double waitTime = timeToWait / 100;
   waitTime += 0.000000;
   sscanf(timeStr, "%lf", &toTime);
   toTime += waitTime;

   while (tempDouble < toTime )
   {
      // keeps going until timer is equal to or greater than timer
      accessTimer( LAP_TIMER, tempStr ); 
      sscanf(timeStr, "%lf", &tempDouble);
   }
}

PCB_LL *createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr )
{
   PCB_LL *headNodePtr = NULL;
   PCB_LL *currentNodePtr = NULL;
   OpCodeType *tempPtr = currentPtr;

   accessTimer( LAP_TIMER, timeStr ); //possibly initialize timeStr
   printf("%s, OS: Create Process Control Blocks \n", timeStr );

   headNodePtr = malloc( sizeof( PCB_LL ) );

   int processNum = 0;

   headNodePtr->progCounter = tempPtr;
   headNodePtr->stateOfProcess = NEW;
   headNodePtr->PID = processNum;
   headNodePtr->timeRemaining = calcRemainingTime( tempPtr, configPtr );
   headNodePtr->next = NULL;

   tempPtr = tempPtr->next; //moves one to the right since S will always be at the beginning
   currentNodePtr = headNodePtr;

   while( tempPtr != NULL )  //might be ->next
   {
      //if the process is A, and its a start, then make a new PCB
      if( tempPtr->opLtr == 'A' 
             && (compareString( tempPtr->opName, "start" ) == 0 ) )
         {
            currentNodePtr->next = malloc( sizeof( PCB_LL ) ); //creates the next Process Node
            currentNodePtr = currentNodePtr->next; //sets current Ptr
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


void initialize( Queue *queue )
{
   queue->count = 0;
   queue->head = NULL;
   queue->tail = NULL;
}

int isEmpty( Queue *queue )
{
   return (queue->tail == NULL);
}


 
void simRun( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr )
{
   PCB_LL *localNodePtr = malloc( sizeof( PCB_LL ) );
   PCB_LL *headNodePtr = localNodePtr; //placeholder
   int timeRemaining = calcRemainingTime( currentPtr, configPtr );
   int cycleRate = configPtr->ioCycleRate;
   int currentVal = localNodePtr->progCounter->opValue;

   while( localNodePtr != NULL ) //OUTER PCB LOOP
   {
         accessTimer( ZERO_TIMER, timeStr);
         printf( "OS: System Start\n" );

         accessTimer( LAP_TIMER, timeStr );
         printf( "OS: Create Process Control Blocks\n" );
         createPCB( configPtr, currentPtr, timeStr );

         accessTimer( LAP_TIMER, timeStr );
         printf( "OS: All processes initialized in New state\n" ); //done in createPCB

         accessTimer( LAP_TIMER, timeStr );
         printf( "OS: All processes now set in Ready state\n" );

         while( localNodePtr != NULL )
         {
            localNodePtr->stateOfProcess = READY;
            localNodePtr = localNodePtr->next;
         }

         localNodePtr = headNodePtr;//reset to first process.

         accessTimer( LAP_TIMER, timeStr );
         printf( "OS: Process %d selected with %d ms remaining\n", localNodePtr->PID, timeRemaining );

         accessTimer( LAP_TIMER, timeStr );
         printf( "OS: Process %d set in %d state\n\n", localNodePtr->PID, localNodePtr->stateOfProcess );

         while( localNodePtr != NULL )
         {
            localNodePtr->stateOfProcess = RUNNING;
            localNodePtr = localNodePtr->next;
         }
         localNodePtr = headNodePtr;    

         //start of main loop
         while( localNodePtr->progCounter->opLtr == 'A' 
             && (compareString( localNodePtr->progCounter->opName, "end" ) != 0 ) )
         {
            if ( localNodePtr->progCounter->opLtr == 'P' )//P
            {
               runTimer( currentVal * cycleRate );
            }

            else if( localNodePtr->progCounter->opLtr == 'I' ||
                        localNodePtr->progCounter->opLtr == 'O' ) //I/O
            {
               pthread_t thread0;
               int runTime = cycleRate * currentVal;
               pthread_create( &thread0, NULL, threadEntry, &runTime);
               pthread_join( thread0, NULL );
            }

            else //M
            {
               MMU *newMMU = malloc(sizeof( MMU ) );
               MMU *temp = newMMU;
               int memAvail = configPtr->memAvailable;
               int offSet = currentVal % 1000; //AAA
               currentVal -= offSet; //SSBBBAAA - AAA = SSBBB
               int base = currentVal % 1000; //BBB
               int ID = currentVal - base; //SSBBB - BBB = SS

               newMMU->memID = ID;
               newMMU->memBase = base;
               newMMU->memOffSet = offSet;
               memAvail -= newMMU->memOffSet; //Avail - offset = avail

               while(temp->next)
               {
                  if( newMMU->memOffSet <= memAvail ) //if offset is within avail
                  {
                     //report success
                     printf( "MMU succesful allocate" );
                  }
                  else
                  {
                     //create fake segfault ***
                     printf( ", OS: Process: # experiences segmentaton fault " );
                     localNodePtr = localNodePtr->next; //skip to next Process
                  }
               }

               free( newMMU );
            }
            
            localNodePtr->progCounter = localNodePtr->progCounter->next;
            
         }

         localNodePtr = localNodePtr->next;
         

   }   

   free( localNodePtr );

}

void runBubbleSort( PCB_LL *startNodePtr )
{
   Boolean swapped = True;
   PCB_LL *tempPtr;
   PCB_LL *currentNodePtr;

   int currentVal = currentNodePtr->progCounter->opValue;
   int nextVal = currentNodePtr->progCounter->next->opValue;

   if( startNodePtr == NULL )
      {
         return;
      }
   do
   {
      swapped = False;
      tempPtr = startNodePtr;

      while( tempPtr->next != currentNodePtr )
      {
         if( currentVal > nextVal )
         {
            swap( tempPtr, tempPtr->next );
            swapped = True;
         }
      }
      currentNodePtr = tempPtr;
   } 
   while ( swapped );
   
}

void swap( PCB_LL *ptrOne, PCB_LL *ptrTwo )
{
   PCB_LL *valOne = ptrOne->progCounter->opValue;
   PCB_LL *valTwo = ptrTwo->progCounter->opValue;

   int temp = valOne;
   valOne = valTwo;
   valTwo = temp;
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
   PCB_LL *pcbPtr = malloc( sizeof( PCB_LL ) );
   timeStr = (char *) malloc( MAX_STR_LEN );
   char* displayStr = (char *) malloc( MAX_STR_LEN );
   char *messageStr = (char *) malloc( MAX_STR_LEN );
   char operatingChar = currentPtr->opLtr;
   MMU *mmuPtr = malloc( sizeof( MMU ) );
   
   displayStr = (", Process: %d ", pcbPtr->PID);  

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

      case 'M':

         if( compareString( currentPtr->opName, "allocate" ) == 0 )
         {
            messageStr = ", MMU attempt to allocate %d\n", currentPtr->opValue;
         }
         else
         {
            messageStr = ", MMU attempt to access %d\n", currentPtr->opValue;
         }
         
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



   void configOut( ConfigDataType *configPtr, char *fileName )
   {
      printf( "Version                     :%f\n", configPtr->version );
      printf( "Program file name           :%f\n", configPtr->metaDataFileName );
      printf( "CPU schedule selection      :%f\n", configPtr->cpuSchedCode );
      printf( "Quantum time                :%f\n", configPtr->quantumCycles);
      printf( "Memory Available            :%f\n", configPtr->memAvailable );
      printf( "Process cycle rate          :%f\n", configPtr->procCycleRate );
      printf( "I/O cycle rate              :%f\n", configPtr->ioCycleRate );
      printf( "Log to section              :%f\n", configPtr->logToCode );
      printf( "Log file name               :%f\n", configPtr->logToFileName );
   }

   
}
