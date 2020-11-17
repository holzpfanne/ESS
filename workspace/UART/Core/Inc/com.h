#ifndef _com_h_
#define _com_h_

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_stdint.h>

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htimx);

#endif
