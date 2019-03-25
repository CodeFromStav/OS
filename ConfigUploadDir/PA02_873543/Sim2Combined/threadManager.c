#include "threadManager.h"

//Thread Entry Function
void *threadEntry( void *param )
{
   // variables
   char* displayStr = ", Process: 0, ";
   char *timeStr = (char *) malloc(MAX_STR_LENGTH);
   char *messageStr = (char *) malloc(MAX_STR_LENGTH);
   //cast to ProcessControlBlock
   ProcessControlBlock *pcb = (ProcessControlBlock *)param;
   // I have access to the OpCode linked list and Config data
   OpCode *tempPtr = pcb->currentPtr;
   char operatingChar = tempPtr->opLtr;

   switch( operatingChar )
   {
   case 'A':
   // Program application used with Start and End
   // this is the only case where I check for start and end
      if( opName == "start" )
        {
           messageStr = "run operation start\n";
        }
      else if( opName == "end" )
        {
           messageStr = "run operation end\n";
        }
      accessTimer( LAP_TIMER, &timeStr ); 
      createDisplayStr ( &displayStr, timeStr, messageStr );
      display( pcb->monitorFlag, pcb->fileFlag, &displayString ,pcb->fileBuffer, 
            pcb->currentIndex );
      pcb->currentIndex++;
      // no logic for waiting because each A(operation) always has 0ms as 
      // operation time
   break;
/*
   case 'M':
   // Memory Operations
      if( opName == "allocate" )
        {
           messageStr = "allocating memory\n";
        }
      else if( opName == "access" )
        {
           messageStr = "accessing memory\n";
        }
      accessTimer( LAP_TIMER, &timeStr ); 
      createDisplayStr ( &displayStr, timeStr, messageStr );
      display( pcb->monitorFlag, pcb->fileFlag, &displayString ,pcb->fileBuffer, 
            pcb->currentIndex );
      pcb->currentIndex++;
      
      //sleep for amount of time specified
      threadSleeper( tempPtr->opValue, timeStr );

      messageStr = "finished memory operation\n"
      accessTimer( LAP_TIMER, &timeStr ); 
      createDisplayStr ( &displayStr, timeStr, messageStr );
      display( pcb->monitorFlag, pcb->fileFlag, &displayString ,pcb->fileBuffer, 
            pcb->currentIndex );
      pcb->currentIndex++;
      //end of memory operation
   break;
*/

   case 'P':
   // Process used with run
   messageStr = "Program run\n";
   accessTimer( LAP_TIMER, &timeStr ); 
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //sleep for amount of time specified
   threadSleeper( tempPtr->opValue, timeStr );
   
   break;

   
   case 'I':
   // Input used with descriptors such as harddrive and keyboard
   messageString = tempPtr->opName;
   concatenateString( messageString, " input start\n" );
   accessTimer( LAP_TIMER, &timeStr ); 
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //sleep for amount of time specified
   threadSleeper( tempPtr->opValue, timeStr );
   
   messageString = tempPtr->opName;
   concatenateString( messageString, " input end\n" );
   accessTimer( LAP_TIMER, &timeStr ); 
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;
   break;

   case 'O':
   // Output used with descriptors
   messageString = tempPtr->opName;
   concatenateString( messageString, " output start\n" );
   accessTimer( LAP_TIMER, &timeStr ); 
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;

   //sleep for amount of time specified
   threadSleeper( tempPtr->opValue, timeStr );
   
   messageString = tempPtr->opName;
   concatenateString( messageString, " output end\n" );
   accessTimer( LAP_TIMER, &timeStr ); 
   createDisplayStr ( &displayStr, timeStr, messageStr );
   display( pcb->monitorFlag, pcb->fileFlag, &displayString , pcb->fileBuffer, 
            pcb->currentIndex );
   pcb->currentIndex++;
   break;
   }
   // free memory
   free ( timeStr );
   free ( messageStr );
}

//Thread wait function ( for I/O )
void threadSleeper ( int timeToWait, char *timeStr )
{
   double toTime, tempDoub;
   char *tempStr  = (char *) malloc(MAX_STR_LENGTH);

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
      accessTimer( LAP_TIMER, &tempStr ); 
      sscanf(timeStr, "%lf", &tempDouble);
   }
   // free memory
   free( tempStr );
   //exit function
}