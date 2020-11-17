#include <com.h>

extern DMA_HandleTypeDef hdma_usart1_rx;

extern char RX_Buffer[16];
char cmd[16];

#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB

void gen_random(char *data)
{
	uint32_t lower, upper;
	//if data is right for random command
	if(sscanf(data, "%u:%u", &lower, &upper) != 2)
	{
		printf("NACK\n");
		return ;
	}
	printf("ACK\n");
	printf("#a,%u\n",(rand()%(upper - lower + 1)) + lower);
}

void process_received()
{
	char command;
	char data[12];

	//if data is in protocol style
	if(sscanf(cmd,"#%c,%s\n",&command, data) == 2)
	{
		switch(command)
		{
			case 'r': gen_random(data);
					  break;
			//  <--  more command's are possible to add here
		}
	}
	else if(strncmp(cmd, "ACK\n",4) == 0)
	{
		//toggel LED for ACK
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	}
	else
	{
		//data not in protocol style
		printf("NACK\n");
	}

	memset((void*)cmd,0,16);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htimx)
{
	static uint32_t neg_index = 16;
	//if for 10ms(time Frequency) no change -> timeout and the read process is finished
	if(hdma_usart1_rx.Instance->CNDTR != 16 && neg_index == hdma_usart1_rx.Instance->CNDTR)
	{
		//copy DMA buffer to cmd buffer and clear DMA buffer
		strcpy(cmd, RX_Buffer);
		memset((void*)RX_Buffer,0,16);

		//reset DMA counter
		__HAL_DMA_DISABLE(&hdma_usart1_rx);
		hdma_usart1_rx.Instance->CNDTR = 16;
		__HAL_DMA_ENABLE(&hdma_usart1_rx);
		neg_index = 16;
		//HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		process_received();
	}
	else
	{
		neg_index = hdma_usart1_rx.Instance->CNDTR;
	}

}

