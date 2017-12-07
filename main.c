#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>




void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  //__HAL_RCC_PWR_CLK_ENABLE();

  //__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  //RCC_OscInitStruct.HSICalibrationValue = 16;
	//RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}




void CircularBlink(uint32_t Delay) {
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_Delay(Delay);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_Delay(Delay);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
	HAL_Delay(Delay);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_Delay(Delay);
}


int i = 0;
//int msTick = 0;

void SysTick_Handler(void){
	
	HAL_IncTick();
	
	
	
	//msTick++;
}

void HAL_Delay(__IO uint32_t Delay){
		uint32_t tickstart = 0U;
		tickstart = HAL_GetTick();
		//printf("\r\nTick Start %d",tickstart);
		while(1)
		{
			if((HAL_GetTick() - tickstart) >= Delay){
				break;
			}				
		}
}


int main(){

	// Reset Everything 
	HAL_Init();
	
	
	// Configure System Clock
	SystemClock_Config();
	
	// Configure Peripheral Clock for specific Block
	__HAL_RCC_GPIOD_CLK_ENABLE();
	


  
	// Initialize Pin as GPIO instance 
	GPIO_InitTypeDef gpIoInitStruct;
	gpIoInitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	gpIoInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpIoInitStruct.Pull = GPIO_PULLUP;
	gpIoInitStruct.Speed = GPIO_SPEED_FAST;

	// Initialize GPIO Pin in block
	HAL_GPIO_Init(GPIOD, &gpIoInitStruct);
	
	CircularBlink(200);
	i=1;
	int b =0;
	while(1){
		
		
		if(i==0){
			CircularBlink(200);
			i=1;
		}else{
			while(1){
				if(b>10){
					b=0;
					i=0;
					break;
				}
				if((b%2)==0){
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
				}else{
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
				}
				HAL_Delay(1000);
				
				b++;
			}
			
		}
	
		

	}


	//return 0;
}

