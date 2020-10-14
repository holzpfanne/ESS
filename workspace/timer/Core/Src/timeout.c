#include "timeout.h"
#include "drivers.h"

/**
 *
 *
 */

_Bool _tim_timeout_blocking(uint16_t seconds, char scaler)
{
	TIM_HandleTypeDef htim16;
	// Scaler range checking
	if(seconds > 65 && scaler == '1' ){return 0;}

	switch (scaler)
	{
	case 'u':
		htim16 = config_timer(seconds, 32);
		break;

	case 'm':
		htim16 = config_timer(seconds, 32000);
		break;

	case '1':
		htim16 = config_timer(seconds*1000, 32000);
		break;
	}
	start_timer(htim16);

	return 1;
}
