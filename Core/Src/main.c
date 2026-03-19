/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char rx_char;
char buffer[20];
char binary[20];
int rx_index = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Printdata(unsigned char data){
	//zeroth bit D0 = PA10
	if((data&0x01) == 0x01){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);}
	//first bit D1 = PB3
	if((data&0x02) == 0x02){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);}
	//second bit D2 = PB5
	if((data&0x04) == 0x04){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);}
	//third bit D3 = PB4
	if((data&0x08) == 0x08){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);}
	//fourth bit D4 = PB10
	if((data&0x10) == 0x10){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);}
	//fifth bit D5 = PA8
	if((data&0x20) == 0x20){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);}
	//sixth bit D6 = PA9
	if((data&0x40) == 0x40){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);}
	//seventh bit D7 = PC7
	if((data&0x80) == 0x80){HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET); }
	else				   {HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);}
}

void lcd_data(unsigned char data){
	Printdata(data);									//pass the data to datalines of lcd
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);	//make RS pin high
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);	//make RW pin low
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);	//make EN pin high
	HAL_Delay(2);										//wait for 2 ms
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);	//make EN pin low
}

void lcd_command(unsigned char cmd){
	Printdata(cmd);										//pass the data to datalines of lcd
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);	//make RS pin low
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);	//make RW pin low
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);	//make EN pin high
	HAL_Delay(2);										//wait for 2 ms
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);	//make EN pin low
}

void lcd_string(char *str,unsigned char length){
	unsigned char i;
	for(i=0;i<length;i++){
		lcd_data(str[i]);
	}
}

void lcd_initialise(void){
	lcd_command(0x38);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x01);
}

void decimal_to_binary(int num, char *bin)
{
    int i = 0;

    if(num == 0)
    {
        bin[0] = '0';
        bin[1] = '\0';
        return;
    }

    while(num > 0)
    {
        bin[i++] = (num % 2) + '0';
        num = num / 2;
    }

    bin[i] = '\0';

    // reverse the binary string
    int j = 0, k = i - 1;
    char temp;

    while(j < k)
    {
        temp = bin[j];
        bin[j] = bin[k];
        bin[k] = temp;
        j++;
        k--;
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  lcd_initialise();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	    HAL_UART_Receive(&huart2, (uint8_t*)&rx_char, 1, HAL_MAX_DELAY);

	    // echo back to terminal
	    HAL_UART_Transmit(&huart2, (uint8_t*)&rx_char, 1, HAL_MAX_DELAY);

	    if(rx_char == '\r' || rx_char == '\n')
	    {
	        buffer[rx_index] = '\0';

	        int number = atoi(buffer);

	        decimal_to_binary(number, binary);

	        lcd_command(0x01);
	        HAL_Delay(2);

	        lcd_command(0x80);
	        lcd_string("Number:",7);
	        lcd_string(buffer, strlen(buffer));

	        lcd_command(0xC0);
	        lcd_string("Binary:",7);
	        lcd_string(binary, strlen(binary));

	        rx_index = 0;
	    }
	    else
	    {
	        if(rx_index < 19)
	        {
	            buffer[rx_index++] = rx_char;
	        }
	    }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin PA6 PA7 PA8
                           PA9 PA10 */
  GPIO_InitStruct.Pin = LD2_Pin|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB3 PB4 PB5
                           PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
