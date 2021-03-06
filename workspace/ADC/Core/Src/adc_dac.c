#include <adc_dac.h>

#include <string.h>

ADC_HandleTypeDef hadc1;
uint32_t adc_channel = 0;
DAC_HandleTypeDef hdac1;
uint32_t dac_channel = 0-1;

uint32_t get_adc_channel(char *portPin)
{
	if(strncmp("PA1", portPin, 3) == 0 || strncmp("A1", portPin, 2) == 0) {return ADC_CHANNEL_6;}
	if(strncmp("PA3", portPin, 3) == 0 || strncmp("A2", portPin, 2) == 0) {return ADC_CHANNEL_8;}
	if(strncmp("PA4", portPin, 3) == 0 || strncmp("A3", portPin, 2) == 0) {return ADC_CHANNEL_9;}
	if(strncmp("PA5", portPin, 3) == 0 || strncmp("A4", portPin, 2) == 0) {return ADC_CHANNEL_10;}
	if(strncmp("PA6", portPin, 3) == 0 || strncmp("A5", portPin, 2) == 0) {return ADC_CHANNEL_11;}
	if(strncmp("PA7", portPin, 3) == 0 || strncmp("A6", portPin, 2) == 0) {return ADC_CHANNEL_12;}
	if(strncmp("PB0", portPin, 3) == 0 || strncmp("D3", portPin, 2) == 0) {return ADC_CHANNEL_15;}
	if(strncmp("PB1", portPin, 3) == 0 || strncmp("D6", portPin, 2) == 0) {return ADC_CHANNEL_16;}
	return 0;
}

uint32_t get_dac_channel(char *portPin)
{
	if(strncmp("PA4", portPin, 3) == 0 || strncmp("A3", portPin, 2) == 0) {return DAC_CHANNEL_1;}
	if(strncmp("PA5", portPin, 3) == 0 || strncmp("A4", portPin, 2) == 0) {return DAC_CHANNEL_2;}
	return (uint32_t)0-1;
}

_Bool adc_pinFree(uint32_t channel)
{
	//only channel 9 and 10 are connected to pins which can also be a DAC
	if ((channel == ADC_CHANNEL_9 && dac_channel == DAC_CHANNEL_1) || (channel == ADC_CHANNEL_10 && dac_channel == DAC_CHANNEL_1))
	{
		return 0;
	}
	return 1;
}

uint8_t _adc_configure(char *portPin)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	uint32_t channel;

	if ((channel = get_adc_channel(portPin)) == 0)
	{
		//pin not known
		return 2;
	}

	//check if Pin is already in use as DAC
	if (!adc_pinFree(channel))
	{
		//pin already in use by a DAC
		return 4;
	}

	//init channel
	adc_channel = channel;
	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		return 3;
	}

	return 0;
}

uint8_t _adc_getval(uint16_t *pValue, char *portPin)
{
	if(get_adc_channel(portPin) != adc_channel) {return 1;}
	HAL_ADC_Start(&hadc1);
	*pValue = HAL_ADC_GetValue(&hadc1);
	return 0;
}

_Bool dac_pinFree(uint32_t channel)
{
	if ((channel == DAC_CHANNEL_1 && adc_channel == ADC_CHANNEL_9) || (channel == DAC_CHANNEL_2 && adc_channel == ADC_CHANNEL_10))
	{
		return 0;
	}
	return 1;
}

uint8_t _dac_configure(char *portPin)
{
	DAC_ChannelConfTypeDef sConfig = {0};
	uint32_t channel;

	if ((channel = get_dac_channel(portPin)) == (uint32_t)0 - 1)
	{
		//pin not known
		return 2;
	}

	//check if Pin is already in use as ADC
	if (!dac_pinFree(channel))
	{
		//pin already as ADC in use
		return 4;
	}

	//Init DAC
	hdac1.Instance = DAC1;
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		return 1;
	}

	sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
	dac_channel = channel;
	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, channel) != HAL_OK)
	{
		return 3;
	}
	HAL_DAC_Start(&hdac1, channel);

	return 0;
}

uint8_t _dac_setval(uint16_t value, char *portPin)
{
	if(get_dac_channel(portPin) != dac_channel){return 2;}
	if (HAL_DAC_SetValue(&hdac1, get_dac_channel(portPin), DAC_ALIGN_12B_R, value) == HAL_OK)
	{
		return 0;
	}
	return 1;
}
