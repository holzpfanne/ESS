#include "drivers.h"

TIM_HandleTypeDef config_timer(uint16_t Prescaler, uint16_t Period)
{
	TIM_HandleTypeDef htim16;

	htim16.Instance = TIM16;
	htim16.Init.Prescaler = Prescaler;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = Period;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim16);

	return htim16;
}

void start_timer(TIM_HandleTypeDef htim16)
{
	HAL_TIM_Base_Start_IT(&htim16);
	//HAL_Delay(1000);
	HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}
