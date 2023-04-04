/*
 ******************************************************************************************
 * @file      main.c
 * @author    GowinSemiconductor
 * @device    Gowin_EMPU(GW1NS-4C)
 * @brief     Main program body.
 ******************************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include "multiple.h"
#include <stdio.h>

/* Declarations ------------------------------------------------------------------*/
void UartInit(void);
void TimerInit(TIMER_TypeDef* TIMERx);
void GPIOInit(void);
void delay_ms(__IO uint32_t delay_ms);

/* Variables ------------------------------------------------------------------*/
volatile uint32_t counter;

/* Functions ------------------------------------------------------------------*/
int main()
{   
  int num=0;
	
	NVIC_InitTypeDef InitTypeDef_NVIC;	//Interrupt handler
	
	SystemInit();	//Initializes system
  UartInit();		//Initializes UART0
	GPIOInit();		//Initializes GPIO
	
  printf("\nUart Initial finished\r\n");
  printf("\nTimer Initial:\r\n");
	printf("\nGPIO Initial:\r\n");
	
  TimerInit(TIMER0);	//Initializes Timer0
	

  counter=0;  //Dispaly the message
	
	//Enable Timer0 interrupt handler
	InitTypeDef_NVIC.NVIC_IRQChannel = TIMER0_IRQn;
  InitTypeDef_NVIC.NVIC_IRQChannelPreemptionPriority = 1;
  InitTypeDef_NVIC.NVIC_IRQChannelSubPriority = 1;
  InitTypeDef_NVIC.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&InitTypeDef_NVIC);

  printf("\nNVIC ENABLE IRQ TIMER0\r\n");
  TIMER_EnableIRQ(TIMER0);
  printf("\nTIMER0 IRQ ENABLE\r\n");
  TIMER_StartTimer(TIMER0);
  printf("\nSTART TIMER0\r\n");
	printf("/************GOWINSEMI*****************/\r\n");
	printf("          GOWIN_EMPU(GW1NS-4C)           \r\n");
	printf("/**************************************/\r\n");
	printf("System initialization finished.\r\n");
	printf("Uart initialization finished.\r\n");
	printf("Multiple initialization finished.\r\n");
	printf("Initialization Status : \r\n");
	printf("--MULTIPLIER = %d\r\n",getMultiplier());
	printf("--MULTIPLICAND = %d\r\n",getMultiplicand());
	printf("--CMD = %d\r\n",getMultipleCmd());
	printf("--RESULT = %d\r\n",getMultipleResult());
/*
	printf("Start first multiple\r\n");
	setMultiplier(20);
	setMultiplicand(48);
	startMultiple();
	printf("Compute Status : \r\n");
	printf("--Multiplier = %d\r\n",getMultiplier());
	printf("--Multiplicand = %d\r\n",getMultiplicand());
	printf("--CMD = %d\r\n",getMultipleCmd());
	
	while(getFinishStatus()==FINISHED_STATUS);
	finishMultiple();
	
	printf("Finished Status : \r\n");
	printf("--Multiplier = %d\r\n",getMultiplier());
	printf("--Multiplicand = %d\r\n",getMultiplicand());
	printf("--CMD = %d\r\n",getMultipleCmd());
	printf("--RESULT = %d\r\n",getMultipleResult());
	printf("Multiple first finished.\r\n");
	
	printf("Start second multiple\r\n");
	setMultiplier(30);
	setMultiplicand(48);
	startMultiple();
	printf("Compute Status : \r\n");
	printf("--Multiplier = %d\r\n",getMultiplier());
	printf("--Multiplicand = %d\r\n",getMultiplicand());
	printf("--CMD = %d\r\n",getMultipleCmd());
	
	while(getFinishStatus()==FINISHED_STATUS);
	finishMultiple();
	
	printf("Finished Status : \r\n");
	printf("--Multiplier = %d\r\n",getMultiplier());
	printf("--Multiplicand = %d\r\n",getMultiplicand());
	printf("--CMD = %d\r\n",getMultipleCmd());
	printf("--RESULT = %d\r\n",getMultipleResult());
	printf("Multiple second finished.\r\n");
	*/
  while(1)
  {
     if(counter==2)
     {
       counter=0;
       printf("\r\n");
			 printf("%d ",num);
			 	printf("--Multiplicand = %d\r\n",getMultiplicand());
			 
       num++;
     }
		 if(num < 30)
		 {
				GPIO_SetBit(GPIO0,GPIO_Pin_0); 	//LED1 on
			 	setMultiplier(0);
		 }
		 else
		 {
				GPIO_ResetBit(GPIO0,GPIO_Pin_0);		//LED1 off
			 	setMultiplier(128);
		 }
		 if(num %2 == 0)
		 {
			 setMultiplicand(64);
		 }
		 else
		 {
			 setMultiplicand(128);
		 }
     if(num==60)
		 {	
       num=0;
		}
  }
}

//Initializes UART0
void UartInit(void)
{
  UART_InitTypeDef UART_InitStruct;
	
  UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
  UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
  UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
  UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
  UART_InitStruct.UART_Hstm = DISABLE;
  UART_InitStruct.UART_BaudRate = 115200;//Baud Rate
	
  UART_Init(UART0,&UART_InitStruct);
}

//Initializes Timer0
void TimerInit(TIMER_TypeDef* TIMERx)
{ 
  TIMERx->INTCLEAR = 0;
  TIMER0->RELOAD=25000026;//Set the value of the Timmer 1s
  TIMER0->VALUE= TIMER0->RELOAD; //Set the init value
  TIMER0->CTRL=0;  // timmer interrupt
	
  printf("TIMERx->INTCLEAR = 0;\r\n");
  printf("TIMER0->RELOAD=25000026;\r\n");
  printf("TIMERx->VALUE= TIMER0->RELOAD;\r\n");
  printf("TIMERx->CTRL = 0;\r\n");
}

//Timer0 interrupt handler
void TIMER0_Handler(void)
{
  if(TIMER_GetIRQStatus(TIMER0) != RESET)
  {
    counter++;
    TIMER_ClearIRQ(TIMER0);
  }
}

//Initializes GPIO
void GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitType;
	
	GPIO_InitType.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0,&GPIO_InitType);

  GPIO_SetBit(GPIO0,GPIO_Pin_0);
}

//delay ms
void delay_ms(__IO uint32_t delay_ms)
{
	for(delay_ms=(SystemCoreClock>>13)*delay_ms; delay_ms != 0; delay_ms--);
}
