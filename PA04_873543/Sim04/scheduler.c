#include "ProcessCtrl.h"
#include "StringUtils.h"
#include "scheduler.h"
#include <stdio.h>



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

void enqueue( Queue *queue, int value )
{
   //if( queue->count < )    Do I need a capacity?

   PCB_LL *tempNode;
   tempNode = malloc( sizeof( PCB_LL ) );
   tempNode->PID = value; //NEEDS TO FIX
   tempNode->next = NULL;
   if( !isEmpty( queue ) )
   {
      queue->tail->next = tempNode;
      queue->tail = tempNode;
   }
   else
   {
      queue->head = queue->tail = tempNode;
   }
   queue->count++;
   
   //enqueueing a process 
   //free during dequeue
}

int dequeue( Queue *queue )
{
   PCB_LL *tempNode;
   int nodeVal = queue->head->PID;
   tempNode = queue->head;
   queue->head = queue->head->next;
   queue->count--;
   free( tempNode );
   return nodeVal;
}



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

      //runs processes with shortest time remaining
      //use the bubble sort created
   }



   //check if scheduler says "FCFS-P"
   else if( compareString( scheduler, "FCFS-P" ) )
   {
      //

   }



   //check if scheduler says "SRTF-P"
   else if( compareString( scheduler, "SRTF-P" ) )
   {
      //

   }

   

   //check if scheduler says "RR-P"
   else if( compareString( scheduler, "RR-P" ) )
   {

   }
}