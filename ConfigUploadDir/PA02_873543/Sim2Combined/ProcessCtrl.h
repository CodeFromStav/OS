#ifndef PROCESSCTRL_H
#define PROCESSCTRL_H

#include "MetaDataAccess.h"
#include "StringUtils.h"
#include "ConfigAccess.h"


struct PCB_LL *LL_headNodePtr = NULL;

//create enum with 5 states
 typedef enum 
 { 
	 NEW, READY, RUNNING, WAITING, EXIT
 } States;



//typedef linkedlist
typedef struct PCB_LL
	{
		//PID
		int PID;
		double timeRemaining;
		States stateOfProcess;
	

		
		struct PCB_LL * next;

	} PCB_LL;

//iterate through and initialize these based on the Prefix




void simRun(  ConfigDataType *configPtr, OpCodeType *currentPtr );

void createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr );
void ProcessType ( ConfigDataType *configPtr, OpCodeType *currentPtr );
int calcRemainingTime( OpCodeType *currentPtr , ConfigDataType *configPtr );


#endif