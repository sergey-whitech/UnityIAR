#include "main.h"
#include <stdio.h>
#include <intrinsics.h>

#if defined(UNITY_TEST)
  #include "unity.h"
  #include "unity_fixture.h"

  void RunAllTests(void);
#endif

//------------------------------------------------------------------------------
inline void DWT_Init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0U;
}

//------------------------------------------------------------------------------
inline uint32_t DWT_GetCounter(void)
{
	return DWT->CYCCNT;
}

//------------------------------------------------------------------------------
void SystemClock_Config(void);
void Configure_GPIO(void);

//------------------------------------------------------------------------------
int main(void)
{
#if !defined(UNITY_TEST_HOST)  
  SystemClock_Config();
  Configure_GPIO();
#endif
  
#if !defined(UNITY_TEST)  
  while (1)
  {
    LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN);
    LL_mDelay(150);
  }
#else
  __disable_interrupt();
  DWT_Init();
  UnityMain(0, NULL, RunAllTests);
  printf ("Execution time %d ticks\n", DWT_GetCounter());
  while(1);
#endif
}

//------------------------------------------------------------------------------
void Configure_GPIO(void)
{
  LED2_GPIO_CLK_ENABLE();

  LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinSpeed(LED2_GPIO_PORT, LED2_GPIO_PIN, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinPull(LED2_GPIO_PORT, LED2_GPIO_PIN, LL_GPIO_PULL_NO);
}

//------------------------------------------------------------------------------
void SystemClock_Config(void)
{
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_C2_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  LL_RCC_SetAHB4Prescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  LL_RCC_MSI_Disable();
  while(LL_RCC_MSI_IsReady() != 0)
  {
  }

  LL_Init1msTick(16000000);

  LL_SetSystemCoreClock(16000000);
}

//------------------------------------------------------------------------------
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1)
  {
  }
}
#endif
