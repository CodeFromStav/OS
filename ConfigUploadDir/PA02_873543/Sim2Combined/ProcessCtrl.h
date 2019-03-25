#ifndef PROCESSCTRL_H
#define PROCESSCTRL_H

#include "MetaDataAccess.h"
#include "StringUtils.h"
#include "ConfigAccess.h"


// struct PCB_LL *LL_headNodePtr = NULL;

//create enum with 5 states
 typedef enum 
 { 
	 NEW, READY, RUNNING, WAITING, EXIT
 } States;



//typedef linkedlist
typedef struct PCB_LL
	{
		int PID;
		//processName
		//counter for next process
		
		States stateOfProcess;
	
		double timeRemaining;

		
		struct PCB_LL * next;

	} PCB_LL;

//config data structure
typedef struct
   {
      OpCodeType *currentPtr;
      ConfigDataType *accessPtr;
      int currentIndex;
      Boolean monitorFlag;
      Boolean fileFlag;
      char *fileBuffer[];

   } ProgRun;
//iterate through and initialize these based on the Prefix




void simRun(  ConfigDataType *configPtr, OpCodeType *currentPtr );
void createDisplayString ( char *displayStr, char *timeStr, char *messageStr );
void display( Boolean monitorFlag, Boolean fileFlag, char *str ,
              char **fileBuffer, int currentIndex);

int calcRemainingTime( OpCodeType *currentPtr , ConfigDataType *configPtr );
void logDump( ProgRun *pcb);



//void ProcessType ( ConfigDataType *configPtr, OpCodeType *currentPtr );


#endif