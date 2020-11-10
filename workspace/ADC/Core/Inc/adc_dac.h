#ifndef _adc_dac_h_
#define _adc_dac_h_

#include <sys/_stdint.h>
#define HAL_DAC_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED

#include "stm32l4xx_hal.h"

/*! \brief Function _adc_configure() initializes the ADC for single conversion
 *         of the given portPin.
 *  \param portPin is the port pin that shall be converted as string
 *  			   e.g.: "PA3", "A7"
 *  \returns 0 upon success, >0 on error
 */
uint8_t _adc_configure(char *portPin);

/*! \brief Function _adc_getval() will start an analog to digital
 *         conversion of a provided portPin and write the result to
 *         the provided address.
 *  \param *pValue is the address where the result will be written to
 *  \param portPin is the port pin that shall be converted
 *  \returns 0 upon success, >0 on error
 */
uint8_t _adc_getval(uint16_t *pValue, char *portPin);

/*! \brief Function _dac_setval() will configure the DAC to output
 *         an analog value at the given port pin.
 *  \param value is the digital representation of the value to convert
 *  \param portPin is the port number where to output the value
 *  \return 0 upon success, >0 otherwise
 */
uint8_t _dac_setval(uint16_t value, char *portPin);

/*! \brief Function _dac_configure() initializes the DAC
 *         of the given portPin.
 *  \param portPin is the port pin that shall be converted
 *  			   e.g.: "PA4", "A3"
 *  \returns 0 upon success, >0 on error
 */
uint8_t _dac_configure(char *portPin);


#endif
