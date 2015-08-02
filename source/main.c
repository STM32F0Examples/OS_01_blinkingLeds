#include "stm32f0xx.h"                  // Device header
#include <cmsis_os.h>                                           // CMSIS RTOS header file

 
void myThread(void const *argument);                             // thread function
osThreadId tid_myThread;                                          // thread id
osThreadDef (myThread, osPriorityNormal, 1, 0);                   // thread object

int init_myThread(void) {

  tid_myThread = osThreadCreate(osThread(myThread), NULL);
  if(!tid_myThread) return(-1);
  
  return(0);
}

int myThread1Counter;

void myThread (void const *argument) {
  while(1){
		myThread1Counter++;
		osDelay(1000);
  }
}

int mainThreadCounter;

int main(void){
	osKernelInitialize();
	init_myThread();
	osKernelStart();//after this main beocmes a thread and the os starts running
	while(1){
		mainThreadCounter++;
		osDelay(1000);
	}
}
