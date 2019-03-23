#include "ConfigAccess.h"
#include "MetaDataAccess.h"
#include "ProcessCtrl.h"
#include "simtimer.h"
#include <pthread.h>


//OpCodeType *LL_headNodePtr;

//my PCB Linked List does not do anything, restructure it.
//Do not need to allocate memory for each next node because the OpCodes are already there!
//Process Type on the right track but does not do what it needs


//runs the whole simulator

void simRun(  ConfigDataType *configPtr, OpCodeType *currentPtr )
{

	pthread_t thread_id; //thread identifier
	pthread_attr_t thread_attr; //set of thread attributes

	pthread_attr_init( &thread_attr ); //sets the default attribute of thread

//arg 1: pointer to thread_id
//arg 2: specifies attributes
//arg 3: name of funtion to be executed for the thread to be created
//arg 4: passes arguements to the function "runner"
	pthread_create( &thread_id, &thread_attr, runner, currentPtr)

	pthread_join( thread_id, currentPtr ); //equivalent of wait() for processes


	char timeString[ MAX_STR_LEN ];

	printf( "\nSystem Start");
	//access at 0 timer
	accessTimer( ZERO_TIMER, timeString );
	//possibly a timeToString call
	//void timeToString( int secTime, int uSecTime, char *timeStr )
	//timeToString( , , timeString );

	printf( "\nCreating Process Control Blocks");
	//call function to create PCB
	//PCB_LL *LinkedList = createPCB( configPtr, currentPtr ); //function needs to create PCBS

	//access timer LAP
	accessTimer( LAP_TIMER, timeString );


//all processes initialized in new state

	//for loop setting new process states to NEW
	while( currentPtr != NULL )
		{
		//	LinkedList->stateOfProcess = NEW;
			currentPtr = currentPtr->next;
		}

	printf( "\nAll processes initilized in " );
	//printf( "%s", LinkedList->stateOfProcess );
	printf( " state");


	//ACCESS TIMER LAP
	accessTimer( LAP_TIMER, timeString );

//all processes initialized in ready state

	//run loop to set in READY state
	while( currentPtr != NULL )
		{
		//	LinkedList->stateOfProcess = READY;
			currentPtr = currentPtr->next;
		}

	printf( "\nAll processes now set in " );
	//printf( "%s", LinkedList->stateOfProcess );
	printf( " state");

	//ACCESS LAP TIMER
	accessTimer( LAP_TIMER, timeString );

	//"Process" + PID + "se;ected with" + RemainingTime + "ms remaining"
	printf( "\n Process " );
//	printf( "%s", LinkedList->PID );
	printf( " selected with ");
//	printf( "%d" , LinkedList->timeRemaining );
	printf( " ms remaining\n" );

	//ACCESS LAP TIMER
	accessTimer( LAP_TIMER, timeString );


	//set Process 0 to running state
	//LinkedList->stateOfProcess = RUNNING;

	//"Process" + PID + "set in " + stateOfOperation + "state"
	printf( "\n Process " );
//	printf( "%s", LinkedList->PID );
	printf( " set in ");
//	printf( "%d" , LinkedList->stateOfProcess );
	printf( " state" );

	//ACCESS LAP TIMER
	accessTimer( LAP_TIMER, timeString );



	//loop

}

void *runner( void *param )
	{

	}



//

// PCB_LL *createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr )
// 	{
// 		PCB_LL *PCB_LocalPtr;
// 		int PID = 0;
// 		double timeRemaining = calcRemainingTime( currentPtr, configPtr );
// 		States stateOfProcess = NEW;
	
// 	}

void createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr )
	{

		PCB_LL *localPtr =  malloc ( sizeof ( PCB_LL ) ); //neeed to point to opCodeType
		localPtr->next = NULL;
		//PCB_LL *headPtr = localPtr;
		//PCB_LL *tailPtr = headPtr;

		if( localPtr->next == NULL )
			{
				localPtr->next = malloc ( sizeof ( PCB_LL ) );



			}
		while( localPtr->next != NULL )
			{

			}


/*int PID;
		double timeRemaining;
		States stateOfProcess;
	

		
		struct PCB_LL * next;
*/
		
	}

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
	