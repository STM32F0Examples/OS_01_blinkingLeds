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
		osDelay(500);
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9));
  }
}

void led_init(void);
int mainThreadCounter;

int main(void){
	led_init();
	osKernelInitialize();
	init_myThread();
	osKernelStart();//after this main beocmes a thread and the os starts running
	while(1){
		mainThreadCounter++;
		GPIO_WriteBit(GPIOB,GPIO_Pin_8,!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8));
		osDelay(250);
	}
}

void led_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	GPIO_InitTypeDef myGPIO;
	GPIO_StructInit(&myGPIO);
	myGPIO.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	myGPIO.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&myGPIO);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
}
