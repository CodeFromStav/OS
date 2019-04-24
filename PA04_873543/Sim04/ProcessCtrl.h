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


typedef struct MMU
	{
		int memID;
		int memBase;
		int memOffSet;

		struct MMU * next;

	} MMU;

//typedef linkedlist
typedef struct PCB_LL
	{
		OpCodeType *progCounter;
		int PID;
		
		States stateOfProcess;
	
		double timeRemaining;

      Boolean MonitorFlag;
      Boolean LogFlag;

		
		struct PCB_LL * next;

	} PCB_LL;

void *threadEntry( void *param);

void threadSleeper ( int timeToWait, char *timeStr );

PCB_LL *createPCB( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr );

void simRun( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr );

void createDisplayString ( char *displayStr, char *timeStr, char *messageStr );

void displayLoc( Boolean monitorFlag, Boolean fileFlag, char *str, ConfigDataType *configPtr );

void outputProc( ConfigDataType *configPtr, OpCodeType *currentPtr, char *timeStr );

void runBubbleSort( PCB_LL *startNodePtr );

void swap( PCB_LL *ptrOne, PCB_LL *ptrTwo );

int calcRemainingTime( OpCodeType *currentPtr , ConfigDataType *configPtr );

void configOut( ConfigDataType *configPtr, char *fileName );


//void logDump( ProgRun *pcb);

#endif