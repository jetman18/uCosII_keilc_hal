#include "app.h"
#include "stm32f1xx_hal.h"
#include "includes.h"


/* task priority  */
#define Start_Task_PRIO          10 
#define LED1_Task_PRIO           5
#define LED2_Task_PRIO           6 
#define LED3_Task_PRIO           4 

/* task size */
#define Start_STK_Size           64
#define LED1_STK_Size            64
#define LED2_STK_Size            64
#define LED3_STK_Size            64

/* task stack */
OS_STK Start_Task_STK[Start_STK_Size];
OS_STK LED1_Task_STK[LED1_STK_Size];
OS_STK LED2_Task_STK[LED2_STK_Size];
OS_STK LED3_Task_STK[LED3_STK_Size];


/* task poiter*/
void start_task(void *pdata);
void LED1_task(void *pdata);
void LED2_task(void *pdata);
void LED3_task(void *pdata);

void start_task(void *pdata)
{
	
	OS_CPU_SR cpu_sr=0;
	 	
	OS_ENTER_CRITICAL(); 

	OSTaskCreate(LED1_task, (void *)0, (OS_STK *)&LED1_Task_STK[LED1_STK_Size-1], LED1_Task_PRIO);
	OSTaskCreate(LED2_task, (void *)0, (OS_STK *)&LED2_Task_STK[LED2_STK_Size-1], LED2_Task_PRIO);
	OSTaskCreate(LED3_task, (void *)0, (OS_STK *)&LED3_Task_STK[LED3_STK_Size-1], LED3_Task_PRIO);

	OSTaskSuspend(Start_Task_PRIO); 
	OS_EXIT_CRITICAL();

}


/* global variable begin  */
OS_FLAG_GRP *initflag; 

OS_FLAGS init_flag = 0x00;

INT8U err;

/* global variable end  */
void app_main(){
    /* init */
	 OSInit();
	
	/*        */
	// mysem = OSSemCreate(1);
	 initflag = OSFlagCreate(init_flag,&err);
	 OSTaskCreate(start_task, (void *)0, (OS_STK *)&Start_Task_STK[Start_STK_Size-1], Start_Task_PRIO);
	
	
     OSStart(); 
	/* end init */

	for(;;){
	
	}
	
}

volatile int k1 = 0;
void LED1_task(void *pdata)
{
    /* task init begin */
	
	
	/* task init end */
		for(;;)
		  {
			 k1++;
			 OSFlagPend(initflag,0x01,OS_FLAG_WAIT_SET_ALL,2000, &err);
             HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			  //OSFlagPost(initflag,0x01,OS_FLAG_CLR, &err);
			  OSTimeDly(100);
			//err1 = OSSemPost(mysem);
		  }
}

volatile int k2 = 0;
void LED2_task(void * pdata)
{
    /* task init begin */
	
	
	/* task init end */
		for(;;)
        {
		     //OSSemPend(mysem,0,(INT8U*)&err2);
		     //task2_count ++;
			 k2++;
			 //OSFlagPost(initflag,0x01,OS_FLAG_SET, &err);
		     OSTimeDly(2000);
        }
}

volatile int k3 = 0;
void LED3_task(void * pdata)
{
    /* task init begin */
	//OSTaskSuspend(LED3_Task_PRIO); 
	   
	/* task init end */
		for(;;)
        {
			k3 ++;
		     //OSSemPend(mysem,0,(INT8U*)&err2);
		     //task2_count ++;
		     OSTimeDly(1000);
        }
}





