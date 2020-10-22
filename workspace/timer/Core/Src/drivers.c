#include "drivers.h"

TIM_HandleTypeDef config_timer(uint16_t Prescaler, uint16_t Period, TIM_TypeDef *timer)
{
	TIM_HandleTypeDef htimX;

	if(timer == TIM6)
	{
		htimX.Instance = timer;
		htimX.Init.Prescaler = Prescaler;
		htimX.Init.CounterMode = TIM_COUNTERMODE_UP;
		htimX.Init.Period = Period;
		htimX.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	}
	else if(timer == TIM16)
	{
		htimX.Instance = timer;
		htimX.Init.Prescaler = Prescaler;
		htimX.Init.CounterMode = TIM_COUNTERMODE_UP;
		htimX.Init.Period = Period;
		htimX.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htimX.Init.RepetitionCounter = 0;
		htimX.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	}

	HAL_TIM_Base_Init(&htimX);

	//Set timer to One-pulse Mode
	//HAL_TIM_OnePulse_Init(&htimX, TIM_OPMODE_SINGLE);

	return htimX;
}

void start_timer(TIM_HandleTypeDef *htimX)
{
	HAL_TIM_Base_Start_IT(htimX);
	sleeplock = 1;
}

void enterSleepMode()
{
	while(sleeplock)
	{
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON , PWR_SLEEPENTRY_WFI);
	}
}
