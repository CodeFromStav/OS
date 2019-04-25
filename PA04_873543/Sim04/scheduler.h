#ifndef SCHEDULER_H
#define SCHEDULER_H

enum
{
   NONE_READY = -666
   
};


typedef struct Queue
{
   int capacity;
	int count;
	PCB_LL *head;
	PCB_LL *tail;

} Queue;







#endif