#include "main.h"

static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;

int main(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  
  /* Configure LED3 and LED4 on STM32L100C-Discovery */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  
  /* Initialize User_Button on STM32L100C-Discovery */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
   
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 1;
  
  while(1)
  {  
    /* Check if the user button is pressed */
    if(STM_EVAL_PBGetState(BUTTON_USER) == SET)
    {
      /* BlinkSpeed: 1 -> 2 -> 0, then re-cycle */
      /* Turn on LD4 Blue LED during 1s each time User button is pressed */
      STM_EVAL_LEDOn(LED3);
      
      /* wait for 1s */
      Delay(500);
      
      /* Turn off LD4 Blue LED after 1s each time User button is pressed */
      STM_EVAL_LEDOff(LED3);
      
      /* Increment the blink speed counter */
      BlinkSpeed++;
      
      /* Default value for blink speed counter */
      if(BlinkSpeed == 3)
      {  
        BlinkSpeed = 0;
      }
    }
    
    /* Test on blink speed */
    if(BlinkSpeed == 2)
    {
      /* LED3 toggles each 100 ms */
      STM_EVAL_LEDToggle(LED4);
      
      /* maintain LED3 status for 100ms */
      Delay(100);
    }
    else if(BlinkSpeed == 1)
    {
      /* LED3 toggles each 200 ms */
      STM_EVAL_LEDToggle(LED4);
      
      /* maintain LED3 status for 200ms */
      Delay(1000);
    }
    else
    {  
      /* LED3 Off */
      STM_EVAL_LEDOff(LED4);
    }
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
