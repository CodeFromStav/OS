//Header for threadManager
#include <stdio.h>
#include "simtimer.h"
//#include "SimMain.h"
#include "ProcessCtrl.h"
//#include <pthreads.h>

// function headers
void *threadEntry( void *param );
void threadSleeper ( int timeToWait, char *timeStr );
