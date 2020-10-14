#ifndef _driver_h_
#define _driver_h_

#include "stm32l4xx_hal.h"
#include <sys/_stdint.h>

TIM_HandleTypeDef config_timer(uint16_t Prescaler, uint16_t Period);

void start_timer(TIM_HandleTypeDef htim16);


#endif
