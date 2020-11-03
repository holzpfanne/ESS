#include "timeout.h"
#include "drivers.h"

/**
 *
 *
 */
_Bool set_timer(uint16_t seconds, char scaler, TIM_TypeDef *timer, TIM_HandleTypeDef *timer_handler)
{
	// Scaler range checking
	if (seconds > 65 && scaler == '1')
	{
		return 0;
	}

	//Set prescaler and counter
	switch (scaler)
	{
	case 'u':
		*timer_handler = config_timer(32, seconds, timer);
		break;

	case 'm':
		*timer_handler = config_timer(32000, seconds, timer);
		break;

	case '1':
		*timer_handler = config_timer(32000, seconds * 1000, timer);
		break;
	}
	return 1;
}

_Bool _tim_timeout_blocking(uint16_t seconds, char scaler)
{
	TIM_HandleTypeDef htim16;
	if(set_timer(seconds, scaler, TIM16, &htim16) == 0) {return 0;}

	start_timer(&htim16);
	enterSleepMode();

	return 1;
}

_Bool _tim_timeout_nonblocking_with_callback(uint16_t seconds, char scaler, void (*callback)())
{
	TIM_HandleTypeDef htim6;
	if(set_timer(seconds, scaler, TIM6, &htim6) == 0) {return 0;}

	timeout_callback = callback;
	start_timer(&htim6);
	return 1;
}
