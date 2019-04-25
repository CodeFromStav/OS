#include "ProcessCtrl.h"
#include "StringUtils.h"
#include "scheduler.h"
#include <stdio.h>




int scheduleNext( PCB_LL **pcb, int processNum, double *interrupts, char *scheduler )
{
   //declare iterators
   int pcbPtr, next, interrupt;

   //check if scheduler says "FCFS-N"
   if( compareString( scheduler, "FCFS-N" ) )
   {

   }


   //check if scheduler says "SJF-N"
   else if( compareString( scheduler, "SJF-N" ) )
   {

   }



   //check if scheduler says "FCFS-P"
   else if( compareString( scheduler, "FCFS-P" ) )
   {

   }



   //check if scheduler says "SRTF-P"
   else if( compareString( scheduler, "SRTF-P" ) )
   {

   }

   

   //check if scheduler says "RR-P"
   else if( compareString( scheduler, "RR-P" ) )
   {

   }
}