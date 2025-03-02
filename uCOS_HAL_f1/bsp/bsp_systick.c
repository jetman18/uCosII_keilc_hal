#include "bsp_systick.h"
#include "stm32f1xx_hal.h"
#include "includes.h"

static uint8_t  fac_us=0;	
static uint16_t fac_ms=0;	



HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /*SystemCoreClock = 8000000; */ 
  //if (HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq)) > 0U)
  if (HAL_SYSTICK_Config(SystemCoreClock / (1000U / (1000/OS_TICKS_PER_SEC))) > 0U)
  {
    return HAL_ERROR;
  }

  /* Configure the SysTick IRQ priority */
  if (TickPriority < (1UL << __NVIC_PRIO_BITS))
  {
    HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
    uwTickPrio = TickPriority;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/*

void SysTickConfig(void)
{

	uint32_t RELOAD=0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//HCLK / 8
	fac_us = SystemCoreClock / 8000000; 

	RELOAD = SystemCoreClock / 8000000;	// cnt/s
	RELOAD *= 1000000 / OS_TICKS_PER_SEC;//RELOAD max 16777216
	fac_ms = 1000 / OS_TICKS_PER_SEC;
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->LOAD = RELOAD;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}



void SysTickConfig(void)
{
	uint32_t OS_reload = 0;
	OS_reload=Reload_1ms*(1000/OS_TICKS_PER_SEC);
	if(SysTick_Config(OS_reload) ==1)
		{
			while(1);
		}
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;// SysTick_CTRL_ENABLE_Msk; 
}

*/