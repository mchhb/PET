/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "config.h"
#include "string.h"
#include "24c16.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__  
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart4, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/************************/
//CONFIG USR_C322 MODE

static const char *para[]=
{
	"+++",
	"a",
	"AT+WMODE=STA\n",
	//"AT+WSTA=GDZYdating,GDZY888888@\n\r",
	"AT+WSTA=HUAWEI_B316_FC7A,88888888\n\r",
	//"AT+WSTA=HUAWEI_B316_EB98,haohanbo123\n",
	"AT+WANN=DHCP\n",
	"AT+WANN=STATIC,Address,Mask,Gateway,Dns\n",
	"AT+WSLK\n",
	"AT+WKMOD=TRANS\n",
	//"AT+SOCKA=TCPC,172.16.40.42,8080\n",
	//"AT+SOCKA=TCPC,172.16.40.39,8999\n",
	"AT+SOCKA=TCPC,118.25.181.199,8999\n",
//	"AT+SOCKA=TCPC,mini.luanling.club,8080\n",
	"AT+ENTM\n"
};
/************************/

/************************/
//USRART1 CONFIG VALUE

Driver driver;
uint8_t test_value = 0;


uint8_t test_c322_value = 0xff;
uint8_t C322_Config_Success = 0;
__IO uint8_t usr_c322 = 0x00;

USART Uart1;
USART Uart2;
uint8_t Noise_SendData[] = {0x01,0x03,0x00,0x00,0x00,0x01,0x84,0x0a};
uint8_t Heart_beat[] = {0xbb,0xbb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t Alarm_Data[] = {0xCC,0xCC,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00};
uint8_t Heart_Rev[] = {0xdd,0xdd,0x01,0x02,0x03,0x04,0x05,0x06,0x00,0x00};
uint8_t work_status = 0;
uint8_t id_name[4];
us8_t work_fault;
uint8_t noise_num = 0;
uint8_t alarm_start = 0;
uint8_t net_work = 1;
uint8_t alarm_times = 0;
uint8_t auto_fooh = 5;
uint8_t net_check = 0;
uint8_t heart_check = 0;
uint8_t Auto_CleanOut(void);
/************************/

/************************/
//MEEP

uint8_t meep_status = 0;

/************************/

/************************/
//LED
uint8_t led_status = 0x03;
uint8_t led_set_work = 0;

/************************/

/************************/
//DOOR
uint8_t door_status = 0;
/************************/

/************************/
//CPU ID
uint32_t Lock_Code;
uint32_t CpuID[3];

/************************/

/************************/
//24c16
uint32_t Buff_test;

/************************/

/************************/

uint16_t Noise_db = 0;

/************************/

/************************/

uint8_t auto_clean = 0;
uint8_t auto_clean_step = 0;

/************************/
/************************/
// TIM2 CONFIG 

uint32_t t2_count_ms[T2_MS_ARRAY_NUM];
uint32_t t1_count_ms;

/************************/
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Config_usr322(void);
void MEEP_SET(uint8_t meep);
void WORK_LED(uint8_t led);
void WORK_DOOR(uint8_t door);
void HC_SR505_Status(void);
uint8_t Noise_Status(void);
uint8_t ModbusCrc16_Receive(unsigned char Frame[], unsigned char Length);
uint8_t ModbusCrc16_Send(unsigned char Frame[], unsigned char Length);
void GetLockCode(void);
void Heart_Beat(void);
void USR_C322_ACTION(void);
void CHECK_STATUS(void);
void READ_WORKSTATUS(void);
void OPEN_DOOR(void);
void test_relay(void);
void C322_CONFIG_Init(void);
void SoftReset(void);
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
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	GetLockCode();
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&Uart1.aRxBuffer, 1);
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&Uart2.aRxBuffer, 1);
	HAL_TIM_Base_Start_IT(&htim2); //使用定时器的时候调用这个函数启动
	HAL_TIM_Base_Start_IT(&htim1); //使用定时器的时候调用这个函数启动
	READ_WORKSTATUS();
	//HAL_TIM_Base_Stop_IT(&htim2);  //停止定时器的时候调用这个函数关闭
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
			//test_relay();
		C322_CONFIG_Init();
		CHECK_STATUS();
		Config_usr322();
		WORK_LED(led_status);
		MEEP_SET(meep_status);
		WORK_DOOR(door_status);
		HC_SR505_Status();
		Noise_Status();
		USR_C322_ACTION();
		Heart_Beat();
		Auto_CleanOut();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
  * @brief  This function Config UsrC322.
  * @param  None
  * @retval : None
  */
void test_relay(void)
{
		if(t2_count_ms[T2_COUNTER_S_10] >= T2_TIMEOUT_S_10)
		{
			t2_count_ms[T2_COUNTER_S_10] = 0;
			test_value++;
			if(test_value%2 == 0)
			{
				START_RELAY2;
				printf("打开\r\n");
			}
			else
			{
				CLOSE_RELAY2;
				printf("关闭\r\n");
			}
			Delay_ms(2000);
			printf("读到信号为 %d。\r\n",READ_RELAY2);
		}
}
void C322_CONFIG_Init(void)
{
			if((test_c322_value == 0)&&(C322_Config_Success == 0))
			{
				test_c322_value++;
				Delay_ms(1000);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
				Delay_ms(8000);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			}
			else if(test_c322_value == 2)
			{
			//	meep_status = MEEP_SHORT_TIME;
			//	t2_count_ms[T2_COUNTER_MS_1500] = 0;
				test_c322_value++;
				C322_Config_Success = 1;
				at24c16_write(0x02,1);
				driver.step = 0x01;
				net_work = 0;
				work_fault.b = 0;
				printf("WIFI模块配置/连接成功!开始正常工作.\r\n");
			}
			if((heart_check >= 2) && (net_check == 5))
			{
				net_check = 0;
				printf("未收到心跳回复，网络断开。\r\n");
			}
			if((heart_check >= 3) && (test_c322_value != 1))
			{
				SoftReset();
			}
}
void SoftReset(void)
{
	__set_FAULTMASK(1);      						
	NVIC_SystemReset();									
}
/**
  * @brief  This function Config UsrC322.
  * @param  None
  * @retval : None
  */
uint8_t Config_usr322(void)
{
	if(C322_Config_Success == 2)
	{
			switch(usr_c322)
			{
				case USR_C322_RESET:
					usr_c322 += USR_C322_UART;
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
					Delay_ms(500);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
					Delay_ms(2000);
				break;
				case USR_C322_UART:
					usr_c322 += USR_C322_UART;
					HAL_UART_Transmit(&huart1, (uint8_t *)para[0],strlen(para[0]), UART_Transmit_Timeout);
				break;
				case USR_C322_CONFIG:
					usr_c322 += USR_C322_UART;
					Delay_ms(1000);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[1],strlen(para[1]), UART_Transmit_Timeout);
				break;
				case USR_C322_MODE:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[2],strlen(para[2]), UART_Transmit_Timeout);
				break;
				case USR_C322_ROUTER:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[3],strlen(para[3]), UART_Transmit_Timeout);
				break;
				case USR_C322_DHCP:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[4],strlen(para[4]), UART_Transmit_Timeout);
				break;
				case USR_C322_CONNECT_ROUTER_STATUS:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[6],strlen(para[6]), UART_Transmit_Timeout);
				break;
				case USR_C322_SERIALAPP:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[7],strlen(para[7]), UART_Transmit_Timeout);
				break;
				case USR_C322_SERVER:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[8],strlen(para[8]), UART_Transmit_Timeout);
				break;
				case USR_C322_WORK:
					usr_c322 += USR_C322_UART;
					Delay_ms(500);
					HAL_UART_Transmit(&huart1, (uint8_t *)para[9],strlen(para[9]), UART_Transmit_Timeout);
				break;
			}
			if((usr_c322 < USR_C322_ENTM_OK) && (t2_count_ms[T2_COUNTER_S_20] >= T2_TIMEOUT_S_20))
			{
				t2_count_ms[T2_COUNTER_S_20] = 0;
				printf("USR-C322 配置不成功。\r\n");
				usr_c322 = 0;
			}
	}
	return 0;
}	

/**
  * @brief  This function USART1 Call Back.
  * @param  None
  * @retval : None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	if(huart->Instance == USART1)
	{
		if(Uart1.Rx_Cnt >= 255)
		{
			Uart1.Rx_Cnt = 0;
			memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff));
		}
		else
		{
			switch(usr_c322)
			{
				case USR_C322_RECEIVE:
					if(Uart1.aRxBuffer == 'a')
					{
						usr_c322 = USR_C322_CONFIG;
						Uart1.Rx_Cnt = 0;
						memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
					}
				break;
				case USR_C322_OK:
					Uart1.RxBuff[Uart1.Rx_Cnt++] = Uart1.aRxBuffer; 
					if(Uart1.Rx_Cnt >= 3)
					{
						if((Uart1.RxBuff[0] == '+')&&(Uart1.RxBuff[1] == 'O')&&(Uart1.RxBuff[2] == 'K'))
						{
							usr_c322 = USR_C322_MODE;
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
						}
					}
				break;
				case USR_C322_ROUTER_STATUS:
						Uart1.RxBuff[Uart1.Rx_Cnt++] = Uart1.aRxBuffer; 
						if((Uart1.RxBuff[Uart1.Rx_Cnt-4] == ',')&&(Uart1.RxBuff[Uart1.Rx_Cnt-3] == '0'))
						{
									HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF);
							//		printf("网络原因，配置不成功！\r\n");
									usr_c322 = USR_C322_DHCP;
								//	usr_c322++;
									Uart1.Rx_Cnt = 0;
									memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
						}
						else if(Uart1.RxBuff[Uart1.Rx_Cnt-6] == ',')
						{
							HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF);
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
							usr_c322++;
						}					
						else if(Uart1.RxBuff[Uart1.Rx_Cnt-5] == ',')
						{
							HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF);
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
							usr_c322++;
						}
						else if(Uart1.RxBuff[Uart1.Rx_Cnt-4] == ',')
						{
							HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF);
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
							usr_c322++;
						}
				break;
				default:
					if(usr_c322 >= USR_C322_ENTM_OK+1)
					{
						Uart1.RxBuff[Uart1.Rx_Cnt++] = Uart1.aRxBuffer; 
						if(Uart1.Rx_Cnt >= 10)
						{
							if(( Uart1.RxBuff[0] == 0xFF) && (id_name[0] == Uart1.RxBuff[2]) && (id_name[1] == Uart1.RxBuff[3])&& \
								(id_name[2] == Uart1.RxBuff[4])&& (id_name[3] == Uart1.RxBuff[5]))
							{
								if(ModbusCrc16_Receive(Uart1.RxBuff,USR_C322_RECEIVE_LENGTH) == True)
								{
									Uart1.Flag = 0;
									Uart1.Rx_Cnt = 0;
									memcpy(Uart1.RxBuffer,&Uart1.RxBuff,Para_Data_Length);
									memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
									Uart1.ReceiveSuccess_Flag = 1;								
								}
								else 
								{
									Uart1.Rx_Cnt = 0;
									Uart1.Flag = 0;
									memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
									Uart1.ReceiveSuccess_Flag = 0;	
								}
							}
							else if((Heart_Rev[0] == Uart1.RxBuff[0]) && (Heart_Rev[1] == Uart1.RxBuff[1]) && (id_name[0] == Uart1.RxBuff[2]) && \
								(id_name[1] == Uart1.RxBuff[3])&& (id_name[2] == Uart1.RxBuff[4])&& (id_name[3] == Uart1.RxBuff[5]) && \
							(Uart1.RxBuff[6] == 0x05)&& (Uart1.RxBuff[7] == 0X06))
							{
									net_check = 5;
									printf("收到心跳回复。\r\n");
									heart_check = 0;
									if((test_c322_value == 1) && (C322_Config_Success == 0))
									{
										test_c322_value++;
									}
									Uart1.Rx_Cnt = 0;
									Uart1.Flag = 0;
									memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
									Uart1.ReceiveSuccess_Flag = 0;	
							}
							else
							{
									Uart1.Rx_Cnt = 0;
									Uart1.Flag = 0;
									memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
									Uart1.ReceiveSuccess_Flag = 0;	
							}
						}
					}
					else
					{
						Uart1.RxBuff[Uart1.Rx_Cnt++] = Uart1.aRxBuffer; 
						if((Uart1.RxBuff[Uart1.Rx_Cnt-1] == 0x0A)&&(Uart1.RxBuff[Uart1.Rx_Cnt-2] == 0x0D)&&(Uart1.RxBuff[Uart1.Rx_Cnt-3] == 'K')&&(Uart1.RxBuff[Uart1.Rx_Cnt-4] == 'O')) //判断结束位
						{
							HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF); 
							if(usr_c322 == USR_C322_ENTM_OK)
							{
								t2_count_ms[T2_COUNTER_S_60] = 60000;
							//	meep_status = MEEP_SHORT_TIME;
							//	t2_count_ms[T2_COUNTER_MS_1500] = 0;
								printf("WIFI AT命令配置成功。\r\n");
								driver.step = 0x01;
								net_work = 0;
								work_fault.b = 0;
							}
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
							usr_c322++;
						}
						else if((Uart1.RxBuff[Uart1.Rx_Cnt-1] == 0x0A)&&(Uart1.RxBuff[Uart1.Rx_Cnt-2] == 0x0D)&&(Uart1.RxBuff[Uart1.Rx_Cnt-6] == 'R')&&(Uart1.RxBuff[Uart1.Rx_Cnt-7] == 'R')) //判断结束位
						{
							HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1.RxBuff, Uart1.Rx_Cnt,0xFFFF); 
							Uart1.Rx_Cnt = 0;
							memset(Uart1.RxBuff,0x00,sizeof(Uart1.RxBuff)); 
							usr_c322++;
						}
					}
				break;
			}
		}
		
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&Uart1.aRxBuffer, 1);  
	}
	if(huart->Instance == USART2)
	{
		if(Uart2.Rx_Cnt >= 7)  
		{
			Uart2.Rx_Cnt = 0;
			Uart2.RxBuff[Uart2.Rx_Cnt++] = Uart2.aRxBuffer;
		}
		else
		{
			Uart2.RxBuff[Uart2.Rx_Cnt++] = Uart2.aRxBuffer; 
			if((Uart2.Rx_Cnt >= Noise_Data_Length) && (ModbusCrc16_Receive(Uart2.RxBuff,Uart2.Rx_Cnt) == True))
			{
				Uart2.ReceiveSuccess_Flag = 1;
				Uart2.Rx_Cnt = 0;
			}
		}
		HAL_UART_Receive_IT(&huart2, (uint8_t *)&Uart2.aRxBuffer, 1);  
	}
}
/**
  * @brief  This function Meep Set.
  * @param  None
  * @retval : None
  */
void MEEP_SET(uint8_t meep)
{
	switch(meep)
	{
		case MEEP_SHORT_TIME:	
			if(t2_count_ms[T2_COUNTER_MS_1500] >= T2_TIMEOUT_MS_1500)
			{
				HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
				meep_status = MEEP_CLOSE;
			}
			else
			{
				HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
			}
		break;
		case MEEP_ALWAY_TIME:
				HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		break;
		default:
				HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
		break;
	}
}
/**
  * @brief  This function WORK LED Set.
  * @param  None
  * @retval : None
  */
void WORK_LED(uint8_t led)
{
	if(t2_count_ms[T2_COUNTER_MS_500] >= T2_TIMEOUT_MS_500)  //500ms
	{
		t2_count_ms[T2_COUNTER_MS_500] = 0;
		switch(led)
		{
			case WORK_FREE:
				CLOSE_LED1; START_LED2;	
			break;
			case WORK_NORMAL:
				if(led_set_work == 0) 		{ CLOSE_LED1;	START_LED2; 	led_set_work = 1; }
				else 											{ CLOSE_LED1;	CLOSE_LED2;		led_set_work = 0; }
			break;
			case WORK_ERROR:
				if(led_set_work == 1) 		{ CLOSE_LED2; START_LED1; 	led_set_work = 0; }
				else 											{ CLOSE_LED2; CLOSE_LED1;		led_set_work = 1; }
		  break;
			case WORK_UNUSUAL:
				CLOSE_LED2; START_LED1;		
			break;
		}
	}
}



/**
  * @brief  This function LOOP LED Set.
  * @param  None
  * @retval : None
  */
void WORK_DOOR(uint8_t door)
{
	switch(door)
		{
			case WORK_NORMAL:
				CLOSE_LED4;START_LED3;	
						
			break;
			default:
				CLOSE_LED3;START_LED4;	
			break;
		}
}
/**
  * @brief  This function Tim2 Counter.
  * @param  None
  * @retval : None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		int i;
		if(htim->Instance == TIM2)
		{
			for(i = 0; i < T2_MS_ARRAY_NUM; i++)
			{
				t2_count_ms[i]++;
				if(t2_count_ms[i] >= T2_TIMEOUT_MAXIMUM)
				{
					t2_count_ms[i] = 0;
				}
			}
		}
		if(htim->Instance == TIM1)
		{
				t1_count_ms++;
		}
}
/**
  * @brief  This function Read HC-SR501.
  * @param  None
  * @retval : None
  */
void HC_SR505_Status(void)
{
	if((READ_LIMIT_SWITCH == 0x00) && (driver.step == 1))
	{
				driver.step = 0x02;
				t2_count_ms[T2_COUNTER_S_10] = 0;
				printf("门关闭，延时10S继续判断，等待。\r\n");
				CLOSE_RELAY2;
	}
	else if((driver.step == 0x02)&&(t2_count_ms[T2_COUNTER_S_10] > T2_TIMEOUT_S_10))
	{
		t2_count_ms[T2_COUNTER_S_10] = 0;
		if((READ_HC_SR505_OUT2 == 0x00) && (READ_HC_SR505_OUT1 == 0x00) && ((READ_LIMIT_SWITCH == 0x00) && (driver.mode == 0x00)))
		{
			CLOSE_RELAY2;
			driver.step = 0x03;
			meep_status = MEEP_SHORT_TIME;
			t2_count_ms[T2_COUNTER_MS_1500] = 0;
			work_fault.BIT2 = 0;
			printf("门关闭，且无宠物，等待接收指令、待机或自动清洗。\r\n");
		}
		else if((((READ_HC_SR505_OUT2 == 0x01) || (READ_HC_SR505_OUT1 == 0x01)) && (driver.mode == 0x01)) && (READ_LIMIT_SWITCH == 0x00))
		{
			CLOSE_RELAY2;
			driver.step = 0x03;
			meep_status = MEEP_CLOSE;
	//		t2_count_ms[T2_COUNTER_MS_1500] = 0;
			printf("门关闭，且有动物，开启工作，等待接收指令。\r\n");
		}
		else if((driver.mode == 0x01) && (READ_HC_SR505_OUT1 == 0x00) && (READ_HC_SR505_OUT2 == 0x00))
		{
			printf("未检测到宠物。请放入宠物。\r\n");
		//	OPEN_DOOR();
			driver.step = 0x01;
			t2_count_ms[T2_COUNTER_S_10] = 0;
			meep_status = MEEP_SHORT_TIME;
			t2_count_ms[T2_COUNTER_MS_1500] = 0;
			work_fault.BIT1 = 1;
		}
		else if((driver.mode == 0x00) && ((READ_HC_SR505_OUT1 == 0x01) || (READ_HC_SR505_OUT2 == 0x01)))
		{
			printf("空闲时，检测宠物箱有宠物，发送报警。\r\n");
			driver.step = 0x01;
			meep_status = MEEP_SHORT_TIME;
			t2_count_ms[T2_COUNTER_S_10] = 0;
			t2_count_ms[T2_COUNTER_MS_1500] = 0;
			work_fault.BIT1 = 1;
		}
		if((driver.mode == 0x02) &&((READ_HC_SR505_OUT1 == 0x01) || (READ_HC_SR505_OUT2 == 0x01)))
		{
			//OPEN_DOOR();
			auto_clean = 0xff;
			meep_status = MEEP_SHORT_TIME;
			t2_count_ms[T2_COUNTER_MS_1500] = 0;
			work_fault.BIT2 = 1;
			printf("强制清洗过程中检测到有宠物，发送报警。\r\n");
		}
	}
}
/**
  * @brief  This function OPEN DOOR.
  * @param  None
  * @retval : None
  */
void OPEN_DOOR(void)
{
	t2_count_ms[T2_COUNTER_S_35] = 0;
	START_RELAY1;
	Delay_ms(1000);
	CLOSE_RELAY1;
	Delay_ms(200);
	START_RELAY2;
}
/**
  * @brief  This function Config Noise.
  * @param  None
  * @retval : None
  */
uint8_t Noise_Status(void)
{
	if((t2_count_ms[T2_COUNTER_S_6] > T2_TIMEOUT_S_6)&&(usr_c322 >= USR_C322_ENTM_OK))
	{
		t2_count_ms[T2_COUNTER_S_6] = 0;
		HAL_UART_Transmit(&huart2, (uint8_t *)Noise_SendData,sizeof(Noise_SendData), UART_Transmit_Timeout);
	}
	if(Uart2.ReceiveSuccess_Flag == True)
	{
		Uart2.ReceiveSuccess_Flag = 0;
		Noise_db = ((Uart2.RxBuff[3] << 8) + Uart2.RxBuff[4])/10;
		memset(Uart2.RxBuff,0x00,sizeof(Uart2.RxBuff)); 
		//printf("Noise db is %03d\r\n",Noise_db);
	}
	if(Noise_db >= NOISE_ALARM)
	{
		noise_num++;
		if(noise_num >= 2)
		{
			noise_num = 0;
			Alarm_Data[2] = id_name[0];
			Alarm_Data[3] = id_name[1];
			Alarm_Data[4] = id_name[2];
			Alarm_Data[5] = id_name[3];
			Alarm_Data[6] = 0x00;
			Alarm_Data[7] = Noise_db;
			if(ModbusCrc16_Send(Alarm_Data,sizeof(Alarm_Data)) == True)
			{
				HAL_UART_Transmit(&huart1, Alarm_Data,sizeof(Alarm_Data), UART_Transmit_Timeout);
				printf("噪声报警。\r\n");
			}
		}
	}
	return 0;
}
/**
  * @brief  This function CRC.
  * @param  None
  * @retval : None
  */
uint8_t ModbusCrc16_Receive(unsigned char Frame[], unsigned char Length) 
{
	unsigned int crc16 = 0xffff;
	unsigned char ByteIndex, n;
	for (ByteIndex = 0; ByteIndex < Length - 2; ByteIndex++) 
	{
		crc16 ^= Frame[ByteIndex];
		for (n = 0; n < 8; n++) 
		{
			if (crc16 & 1) 
			{
				crc16 >>= 1;
				crc16 ^= 0xA001;
			} 
			else 
			{
				crc16 >>= 1;
			}
		}
	}
	if((Frame[Length - 2] == (crc16&0xFF)) && (Frame[Length - 1] == crc16 >> 8))
	{
		return True;
	}
	else
	{
		return False;
	}
}
/**
  * @brief  This function CRC.
  * @param  None
  * @retval : None
  */
uint8_t ModbusCrc16_Send(unsigned char Frame[], unsigned char Length) 
{
	unsigned int crc16 = 0xffff;
	unsigned char ByteIndex, n;
	for (ByteIndex = 0; ByteIndex < Length - 2; ByteIndex++) 
	{
		crc16 ^= Frame[ByteIndex];
		for (n = 0; n < 8; n++) 
		{
			if (crc16 & 1) 
			{
				crc16 >>= 1;
				crc16 ^= 0xA001;
			} 
			else 
			{
				crc16 >>= 1;
			}
		}
	}
	Frame[Length - 2] = crc16;
	Frame[Length - 1] = crc16 >> 8;
	return True;
}
/**
  * @brief  This function 原cube HAL库中，重写
  * @param  None
  * @retval : None
  */
void HAL_IncTick(void)
{
	if(time_delay)
		time_delay--;	
}
/**
  * @brief  This function CPU ID.
  * @param  None
  * @retval : None
  */
void GetLockCode(void)
{
	CpuID[0]=HAL_GetUIDw0();
	CpuID[1]=HAL_GetUIDw1();
	CpuID[2]=HAL_GetUIDw2();
	Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	id_name[0] = Lock_Code >> 24;
	id_name[1] = Lock_Code >> 16;
	id_name[2] = Lock_Code >> 8;
	id_name[3] = Lock_Code &0xff;
	printf("设备id：%d\r\n",Lock_Code);
}

/**
  * @brief  This function Auto_CleanOut.
  * @param  None
  * @retval : None
  */
uint8_t Auto_CleanOut(void)
{
	if((driver.mode == 0x02) && (auto_clean == 0x00))
	{
		if((t2_count_ms[T2_COUNTER_S_20] >= T2_TIMEOUT_S_20))
		{
			if((READ_LIMIT_SWITCH != 0x00) || (READ_HC_SR505_OUT1 != 0) || (READ_HC_SR505_OUT2 != 0))
			{
				t2_count_ms[T2_COUNTER_S_20] = 0;
				t2_count_ms[T2_COUNTER_MS_1500] = 0;
				meep_status = MEEP_SHORT_TIME;
				driver.step = 0xff;
				printf("开始强制清洗过程中，门未关或检测到有宠物，报警提示。\r\n");
				work_fault.BIT2 = 1;
			}
			else
			{
				driver.step = 0x03;
				work_fault.BIT2 = 0;
				printf("开始强制清洗过程中，延时20秒后，检测无宠物、门关闭，可继续工作。\r\n");
			}
		}
//		else
//		{
			if((READ_LIMIT_SWITCH == 0x00) && (READ_HC_SR505_OUT1 == 0) && (READ_HC_SR505_OUT2 == 0) && (driver.step == 3))
			{
				printf("开始强制清洗，步骤二。\r\n");
				meep_status = MEEP_CLOSE;
				auto_clean_step++;
				auto_clean++;
				driver.step++;
				t2_count_ms[T2_COUNTER_S_30] = 0;
				t2_count_ms[T2_COUNTER_S_20] = 0;
				START_RELAY6;
				START_RELAY5;
				printf("开始强制清洗过程中，打开清洗泵和雨刷点击，打开时间30秒。\r\n");
				Delay_ms(1000);
				if(READ_RELAY6 == True)
				{
					printf("开始强制清洗过程中，打开清洗泵成功。\r\n");
					work_fault.BIT6 = 0;
				}
				else 
				{
					printf("开始强制清洗过程中，打开清洗泵失败。\r\n");
					work_fault.BIT6 = 1;
				}
				if(READ_RELAY5 == True)
				{
					printf("开始强制清洗过程中，打开雨刷电机成功。\r\n");
					work_fault.BIT5 = 0;
				}
				else 
				{
					work_fault.BIT5 = 1;
					printf("开始强制清洗过程中，打开雨刷电机失败。\r\n");
				}
			}
	//	}
	}
	else if((auto_clean_step == 0x01) && (t2_count_ms[T2_COUNTER_S_30] >= T2_TIMEOUT_S_30))
	{
		printf("开始强制清洗过程中，步骤三。\r\n");
		printf("开始强制清洗过程中，到30秒，关闭雨刷电机，清洗泵在打开10秒。\r\n");
		auto_clean_step++;
		CLOSE_RELAY5;
		Delay_ms(500);
		printf("开始强制清洗过程中，关闭雨刷电机。\r\n");
		if(READ_RELAY5 == False)
		{
			printf("开始强制清洗过程中，关闭雨刷电机成功。\r\n");
			work_fault.BIT5 = 0;
		}
		else 
		{
			printf("开始强制清洗过程中，关闭雨刷电机失败。\r\n");
			work_fault.BIT5 = 1;
		}
		t2_count_ms[T2_COUNTER_S_10] = 0;
	}
	else if((auto_clean_step == 0x02) && (t2_count_ms[T2_COUNTER_S_10] >= T2_TIMEOUT_S_10))
	{
		printf("开始强制清洗过程中，步骤四\r\n");
		printf("开始强制清洗过程中，到40秒，关闭雨刷清洗泵。\r\n");
		auto_clean_step++;
		CLOSE_RELAY6;
		printf("开始强制清洗过程中，关闭清洗泵。\r\n");
		Delay_ms(500);
		if(READ_RELAY6 == False)
		{
			printf("开始强制清洗过程中，关闭清洗泵成功。\r\n");
			work_fault.BIT6 = 0;
		}
		else 
		{
			printf("开始强制清洗过程中，关闭清洗泵失败。\r\n");
			work_fault.BIT6 = 1;
		}
	}
	else if(auto_clean_step == 0x03)
	{
		printf("开始强制清洗过程中，步骤五。\r\n");
		auto_clean_step++;
		START_RELAY7;
		printf("开始强制清洗过程中，打开吹风机，打开时间60秒。\r\n");
		Delay_ms(1000);
		if(READ_RELAY7 == True)
		{
			printf("开始强制清洗过程中，打开吹风机成功。\r\n");
			work_fault.BIT7 = 0;
		}
		else 
		{
			printf("开始强制清洗过程中，打开吹风机失败。\r\n");
			work_fault.BIT7 = 1;
		}
		t2_count_ms[T2_COUNTER_S_60] = 0;
	}
	else if((auto_clean_step == 0x04) && (t2_count_ms[T2_COUNTER_S_60] >= T2_TIMEOUT_S_60))
	{
		printf("开始强制清洗过程中，步骤六。\r\n");
		auto_clean_step++;
		CLOSE_RELAY7;
		printf("开始强制清洗过程中，到60秒，关闭吹风机。\r\n");
		Delay_ms(500);
		if(READ_RELAY7 == False)
		{
			printf("开始强制清洗过程中，关闭吹风机成功。\r\n");
			work_fault.BIT7 = 0;
		}
		else 
		{
			printf("开始强制清洗过程中，关闭吹风机失败。\r\n");
			work_fault.BIT7 = 1;
		}
		START_RELAY10;
		printf("开始强制清洗过程中，打开紫外线消毒灯，打开时间120秒。\r\n");
		t2_count_ms[T2_COUNTER_S_120] = 0;
	}
	else if((auto_clean_step == 0x05) && (t2_count_ms[T2_COUNTER_S_120] >= T2_TIMEOUT_S_120))
	{
		printf("开始强制清洗过程中，步骤七。\r\n");
		auto_clean_step = 0x00;
		auto_clean = 0x00;
		printf("开始强制清洗过程中，到120秒，关闭紫外线消毒灯。\r\n");
		CLOSE_RELAY10;
		printf("开始强制清洗过程中，关闭紫外线消毒灯。\r\n");
		driver.mode = 0x00;
		at24c16_write(0x00,driver.mode);
		Alarm_Data[2] = id_name[0];
		Alarm_Data[3] = id_name[1];
		Alarm_Data[4] = id_name[2];
		Alarm_Data[5] = id_name[3];
		Alarm_Data[6] = 0x04;
		Alarm_Data[7] = 0x00;
		if(ModbusCrc16_Send(Alarm_Data,sizeof(Alarm_Data)) == True)
		{
			HAL_UART_Transmit(&huart1, Alarm_Data,sizeof(Alarm_Data), UART_Transmit_Timeout);
			printf("自动清洗完成。\r\n");
			meep_status = MEEP_SHORT_TIME;
			t2_count_ms[T2_COUNTER_MS_1500] = 0;
		}
		
		return True;
	}
	return False;
}

/**
  * @brief  This function heartbeat.
  * @param  None
  * @retval : None
  */
uint8_t aa = 0;
uint8_t bb = 0;
void Heart_Beat(void)
{
	if((t2_count_ms[T2_COUNTER_S_60] > T2_TIMEOUT_S_60)&&(usr_c322 >= USR_C322_ENTM_OK))
	{
		t2_count_ms[T2_COUNTER_S_60] = 0;
		Heart_beat[2] = id_name[0];
		Heart_beat[3] = id_name[1];
		Heart_beat[4] = id_name[2];
		Heart_beat[5] = id_name[3];
		Heart_beat[6] = work_status;
		Heart_beat[7] = work_fault.b;
		if(ModbusCrc16_Send(Heart_beat,sizeof(Heart_beat)) == True)
		{
			HAL_UART_Transmit(&huart1, Heart_beat,sizeof(Heart_beat), UART_Transmit_Timeout);
		//	net_check++;
			printf("心跳。\r\n");
			heart_check++;
		}
		
	}
}
/**
  * @brief  This function open door.
  * @param  None
  * @retval : None
  */
void USR_C322_ACTION(void)
{
	if(Uart1.ReceiveSuccess_Flag == True)
	{
		
		Uart1.ReceiveSuccess_Flag = 0;
		if((driver.mode == 0x02) && (Uart1.RxBuffer[6] != 0x10) && (work_fault.BIT2 == 0))
		{
			memset(Uart1.RxBuffer,0x00,sizeof(Uart1.RxBuffer));
			Uart1.TxBuffer[0] = 0xAA;
			Uart1.TxBuffer[1] = 0xAA;
			Uart1.TxBuffer[2] = id_name[0];
			Uart1.TxBuffer[3] = id_name[1];
			Uart1.TxBuffer[4] = id_name[2];
			Uart1.TxBuffer[5] = id_name[3];
			Uart1.TxBuffer[6] = 0x11;
			if(ModbusCrc16_Send(Uart1.TxBuffer,sizeof(Uart1.TxBuffer)) == True)
			{
				HAL_UART_Transmit(&huart1, Uart1.TxBuffer,sizeof(Uart1.TxBuffer), UART_Transmit_Timeout);
				printf("拒绝操作，在强制消毒过程中，回复。\r\n");
			}
			return;
		}
		switch(Uart1.RxBuffer[6])
		{
			case 0x01:
				if(Uart1.RxBuffer[7] == True)
				{
					alarm_start = 2;
					if(READ_LIMIT_SWITCH == False)
					{
						printf("收到开门指令。\r\n");
						OPEN_DOOR();
						if(READ_LIMIT_SWITCH == True)
						{
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("门故障。\r\n");
							work_fault.BIT0 = 1;
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("门在打开状态。\r\n");
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				Uart1.TxBuffer[6] = 0x01;
			break;
			case 0x02:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开柜门灯指令。\r\n");
					if(READ_RELAY2 == False)
					{
						START_RELAY2;
						Delay_ms(500);
						if(READ_RELAY2 == True)
						{
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("柜门灯故障。\r\n");
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("柜门灯已在打开状态。\r\n");
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关柜门灯指令。\r\n");
					CLOSE_RELAY2;
					Delay_ms(500);
					if(READ_RELAY2 == True)
					{
						printf("关柜门灯故障。\r\n");
						Uart1.TxBuffer[7] = 0x01;
					}
					else 
					{
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x02;
			break;
			case 0x03:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开喂水阀指令，喂水15秒。\r\n");
					if(READ_RELAY3 == False)
					{
						START_RELAY3;
						Delay_ms(500);
						if(READ_RELAY3 == True)
						{
							auto_fooh = 0x01;
							t2_count_ms[T2_COUNTER_S_15] = 0;
							work_fault.BIT4 = 0;
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("喂水阀故障。\r\n");
							work_fault.BIT4 = 1;
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("喂水阀在打开状态。\r\n");
						work_fault.BIT4 = 0;
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关喂水阀指令。\r\n");
					CLOSE_RELAY3;
					Delay_ms(500);
					if(READ_RELAY3 == True)
					{
						printf("关喂水阀故障。\r\n");
						work_fault.BIT4 = 1;
						Uart1.TxBuffer[7] = 0x01;
					}
					else 
					{
						printf("喂水阀在打开状态。\r\n");
						work_fault.BIT4 = 0;
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x03;
			break;
			case 0x04:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开喂食阀指令，10秒。\r\n");
					if(READ_RELAY4 == False)
					{
						START_RELAY4;
						Delay_ms(500);
						if(READ_RELAY4 == True)
						{
							t2_count_ms[T2_COUNTER_S_10] = 0;
							auto_fooh = 0x02;
							work_fault.BIT5 = 0;
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("喂食阀故障。\r\n");
							work_fault.BIT5 = 1;
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("喂食阀在打开状态。\r\n");
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关喂食阀指令。\r\n");
					CLOSE_RELAY4;
					Delay_ms(500);
					if(READ_RELAY4 == True)
					{
						printf("关喂食阀故障。\r\n");
						work_fault.BIT5 = 1;
						Uart1.TxBuffer[7] = 0x01;
					}
					else 
					{
						work_fault.BIT5 = 0;
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x04;
			break;
			case 0x05:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开雨刷器指令。\r\n");
					if(READ_RELAY5 == False)
					{
						START_RELAY5;
						Delay_ms(1000);
						if(READ_RELAY5 == True)
						{
							work_fault.BIT6 = 0;
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("雨刷器故障。\r\n");
							work_fault.BIT6 = 1;
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("雨刷器在打开状态。\r\n");
						work_fault.BIT6 = 0;
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关雨刷器指令。\r\n");
					CLOSE_RELAY5;
					Delay_ms(500);
					if(READ_RELAY5 == True)
					{
						printf("关雨刷器故障。\r\n");
						Uart1.TxBuffer[7] = 0x01;
						work_fault.BIT6 = 1;
					}
					else 
					{
						work_fault.BIT6 = 0;
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x05;
			break;
			case 0x06:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开清洗泵指令。\r\n");
					if(READ_RELAY6 == False)
					{
						START_RELAY6;
						Delay_ms(500);
						if(READ_RELAY6 == True)
						{
							
							work_fault.BIT7 = 0;
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("清洗泵故障。\r\n");
							work_fault.BIT7 = 1;
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						printf("清洗泵在打开状态。\r\n");
						work_fault.BIT7 = 0;
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关清洗泵指令。\r\n");
					CLOSE_RELAY6;
					Delay_ms(500);
					if(READ_RELAY6 == True)
					{
						printf("关清洗泵故障。\r\n");
						work_fault.BIT7 = 0x01;
						Uart1.TxBuffer[7] = 0x01;
					}
					else 
					{
						work_fault.BIT7 = 0x00;
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x06;
			break;
			case 0x07:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开吹风机指令。\r\n");
					if(READ_RELAY7 == False)
					{
						START_RELAY7;
						Delay_ms(1000);
						if(READ_RELAY7 == True)
						{
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("吹风机故障。\r\n");
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关吹风机指令。\r\n");
					CLOSE_RELAY7;
					Delay_ms(500);
					if(READ_RELAY7 == True)
					{
						printf("关吹风机故障。\r\n");
						Uart1.TxBuffer[7] = 0x01;
					}
					else 
					{
						Uart1.TxBuffer[7] = 0x00;
					}
				}
				Uart1.TxBuffer[6] = 0x07;
			break;
			case 0x08:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("收到开换气扇指令。\r\n");
					if((READ_RELAY8 == False) && (READ_RELAY9 == False))
					{
						START_RELAY8;
						START_RELAY9;
						Delay_ms(500);
						if((READ_RELAY8 == True) && (READ_RELAY9 == True))
						{
							Uart1.TxBuffer[7] = 0x01;
						}
						else
						{
							printf("换气扇故障。\r\n");
							Uart1.TxBuffer[7] = 0x00;
						}
					}
					else
					{
						Uart1.TxBuffer[7] = 0x02;
					}
				}
				else
				{
					printf("收到关换气扇指令。\r\n");
					CLOSE_RELAY8;
					CLOSE_RELAY9;
					Delay_ms(500);
					if((READ_RELAY8 == False)&&(READ_RELAY9 == False))
					{
						Uart1.TxBuffer[7] = 0x00;
					}
					else 
					{
						printf("关换气扇指令。\r\n");
						Uart1.TxBuffer[7] = 0x01;
					}
				}
				Uart1.TxBuffer[6] = 0x08;
			break;
			case 0x0A:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("接收到打开消毒灯指令。\r\n");
					START_RELAY10;
				}
				else
				{
					printf("接收到关闭消毒灯指令。\r\n");
					CLOSE_RELAY10;
				}
				Uart1.TxBuffer[7] = Uart1.RxBuffer[7];
				Uart1.TxBuffer[6] = 0x0A;
			break;
			case 0x0C:
				if(Uart1.RxBuffer[7] == True)
				{
					printf("接收到打开强制消毒指令。\r\n");
					t2_count_ms[T2_COUNTER_S_20]  = 0;
					driver.mode = 0x02;
					printf("开始强制清洗，步骤1，延时20秒判断。\r\n");
					driver.step = 0xff;
					at24c16_write(0x00,driver.mode);
					Uart1.TxBuffer[7] = 0x01;
				}
				else if(Uart1.TxBuffer[7] == 0x00)
				{
					printf("接收到关闭强制消毒指令。\r\n");
					driver.mode = 0x00;
					at24c16_write(0x00,driver.mode);
					Uart1.TxBuffer[7] = 0x00;
				}
				Uart1.TxBuffer[6] = 0x0B;
			break;	
			case 0x0B:
				if(driver.mode == 0x02)
				{
					Uart1.TxBuffer[7] = 0xFF;
					printf("在消毒中。\r\b");
				}
				else if(Uart1.RxBuffer[7] == True)
				{
					if(driver.mode == 0x01)
					{
						Uart1.TxBuffer[7] = 0xEE;
						printf("在工作中。\r\b");
					}
					else
					{
							alarm_start = 2;//开启工作
							printf("开启工作。\r\n");
							if((READ_RELAY8 == False) || (READ_RELAY9 == False))
							{
								START_RELAY8;
								START_RELAY9;
							}
							if(READ_LIMIT_SWITCH == False)
							{
								OPEN_DOOR();
								if(READ_LIMIT_SWITCH != True)
								{
									work_fault.BIT0 = 1;
									driver.mode = 0x00;
									at24c16_write(0x00,driver.mode);
									Uart1.TxBuffer[7] = 0x00;
								}
								else
								{
									printf("门已开，等待放入宠物，延时35秒。\r\n");
									driver.mode = 0x01;
									driver.step = 0x01;
									work_fault.BIT0 = 0x00;
									at24c16_write(0x00,driver.mode);
									Uart1.TxBuffer[7] = 0x01;
								}
							}
							else
							{
									printf("门一直在开状态，等待放入宠物，延时35秒。\r\n");
									driver.mode = 0x01;
									driver.step = 0x01;
									work_fault.BIT0 = 0x00;
									at24c16_write(0x00,driver.mode);
									Uart1.TxBuffer[7] = 0x02;
							}
					}
				}
				else if(Uart1.TxBuffer[7] == 0x00)
				{
						printf("停止工作。\r\n");
						alarm_start = 0x03;//停止工作
						if((READ_RELAY8 == True) || (READ_RELAY9 == True))
						{
							CLOSE_RELAY8;
							CLOSE_RELAY9;
						}
						if(READ_LIMIT_SWITCH == False)
						{
							OPEN_DOOR();
							if(READ_LIMIT_SWITCH != True)
							{
								work_fault.BIT0 = 0x01;
								driver.mode = 0x01;
								//at24c16_write(0x00,driver.mode);
								Uart1.TxBuffer[7] = 0x00;
							}
							else
							{
								work_fault.BIT0 = 0x00;
								driver.mode = 0x02;
								at24c16_write(0x00,driver.mode);
								Uart1.TxBuffer[7] = 0x01;
								printf("开始强制清洗，步骤一，延时20秒判断。\r\n");
								t2_count_ms[T2_COUNTER_S_20]  = 0;
								driver.step = 0xff;
							}
						}
						else
						{
							driver.mode = 0x02;
							printf("开始强制清洗，步骤一，延时20秒判断。\r\n");
							t2_count_ms[T2_COUNTER_S_20]  = 0;
							driver.step = 0xff;
							Uart1.TxBuffer[7] = 0x02;
						}
				}
				Uart1.TxBuffer[6] = 0x0A;
			break;
			case 0x10:
				printf("强制开门。\r\n");
				if(READ_LIMIT_SWITCH == False)
					{
						OPEN_DOOR();
						if(READ_LIMIT_SWITCH != True)
						{
							work_fault.BIT0 = 0x01;
							Uart1.TxBuffer[7] = 0x00;
						}
						else
						{
							driver.mode = 0x00;
							work_fault.BIT0 = 0x00;
							Uart1.TxBuffer[7] = 0x01;
							at24c16_write(0x00,driver.mode);
						}
					}
					else
					{
						driver.mode = 0x00;
						at24c16_write(0x00,driver.mode);
						Uart1.TxBuffer[7] = 0x02;
					}
					Uart1.TxBuffer[6] = 0x10;
			break;
			case 0x0D:
					Uart1.TxBuffer[6] = 0x0D;
					Uart1.TxBuffer[7] = Noise_db;
			break;
			case 0x0E:
					Uart1.TxBuffer[6] = 0x0E;
					Uart1.TxBuffer[7] = READ_HC_SR505_OUT1 | READ_HC_SR505_OUT2;
			break;
			case 0x0F:
					Uart1.TxBuffer[6] = 0x12;
					Uart1.TxBuffer[7] = 0x00;
			break;
			case 0x12:
					
					at24c16_write(0x00,0x00);
					
					Delay_ms(1000);
			
					SoftReset();
			break;
			case 0x13:
					at24c16_write(0x02,0x00);
			
					Delay_ms(1000);
			   
					SoftReset();
			break;
			case 0x14:
					SoftReset();
			break;
			default:
				Uart1.TxBuffer[6] = 0xff;
			break;
		}
		memset(Uart1.RxBuffer,0x00,sizeof(Uart1.RxBuffer));
		Uart1.TxBuffer[0] = 0xAA;
		Uart1.TxBuffer[1] = 0xAA;
		Uart1.TxBuffer[2] = id_name[0];
		Uart1.TxBuffer[3] = id_name[1];
		Uart1.TxBuffer[4] = id_name[2];
		Uart1.TxBuffer[5] = id_name[3];
		if(ModbusCrc16_Send(Uart1.TxBuffer,sizeof(Uart1.TxBuffer)) == True)
		{
			HAL_UART_Transmit(&huart1, Uart1.TxBuffer,sizeof(Uart1.TxBuffer), UART_Transmit_Timeout);
			printf("回复。\r\n");
		}
	}	
}
/**
  * @brief  This function Check status.
  * @param  None
  * @retval : None
  */
void CHECK_STATUS(void)
{
	work_status = driver.mode;
	if((net_check  <= 4)||(net_check >= 7))
	{
		led_status = WORK_ERROR;
	}
	else if(work_fault.b != 0)
	{
		led_status = WORK_CLOSE;
		//printf("设备故障模式/r/n");
	}
	else
	{
		if(driver.mode == 2)
		{
			led_status = WORK_UNUSUAL;
		}
		else
		{
			led_status = driver.mode;
		}
		//printf("设备 = %d模式/r/n",led_status);
	}
	door_status = READ_LIMIT_SWITCH;
	if((door_status == 0)&&(alarm_start == 1))
	{
		CLOSE_RELAY2;
		alarm_start = 0x00;
		meep_status = MEEP_CLOSE;
	}
	if((door_status == 0) && ((alarm_start == 2)||(alarm_start == 3)))
	{
		CLOSE_RELAY2;
		Delay_ms(500);
		if(READ_RELAY2 == True)
		{
			Uart1.TxBuffer[7] = 0x01;
		}
		else 
		{
			Uart1.TxBuffer[7] = 0x00;
		}
		alarm_start = 0x00;
		t2_count_ms[T2_COUNTER_S_35] = 0;
		meep_status = MEEP_CLOSE;
		alarm_times = 0x00;
	}
//	if(((alarm_start != 2)&&(alarm_start!=3))&&(door_status == 1)&&(t2_count_ms[T2_COUNTER_S_9] >= T2_TIMEOUT_S_9))
//	{
//			t2_count_ms[T2_COUNTER_S_9] = 0;
//			Alarm_Data[2] = id_name[0];
//			Alarm_Data[3] = id_name[1];
//			Alarm_Data[4] = id_name[2];
//			Alarm_Data[5] = id_name[3];
//			Alarm_Data[6] = 0x01;
//			Alarm_Data[7] = 0x01;
//			if(ModbusCrc16_Send(Alarm_Data,sizeof(Alarm_Data)) == True)
//			{
//				HAL_UART_Transmit(&huart1, Alarm_Data,sizeof(Alarm_Data), UART_Transmit_Timeout);
//				printf("未发送指令时，门开启报警\r\n");
//				meep_status = MEEP_SHORT_TIME;
//			}
//	}
	if((t2_count_ms[T2_COUNTER_S_35] > T2_TIMEOUT_S_35) &&(door_status == 1) && (C322_Config_Success != 0))
	{
			t2_count_ms[T2_COUNTER_S_35] = 0;
			Alarm_Data[2] = id_name[0];
			Alarm_Data[3] = id_name[1];
			Alarm_Data[4] = id_name[2];
			Alarm_Data[5] = id_name[3];
			Alarm_Data[6] = 0x02;
			Alarm_Data[7] = alarm_times++;
			if(ModbusCrc16_Send(Alarm_Data,sizeof(Alarm_Data)) == True)
			{
				HAL_UART_Transmit(&huart1, Alarm_Data,sizeof(Alarm_Data), UART_Transmit_Timeout);
				printf("长时间门开启报警，已%d秒。\r\n",(alarm_times)*35);
				meep_status = MEEP_SHORT_TIME;
				t2_count_ms[T2_COUNTER_MS_1500] = 0;
			}
	}
	if((auto_fooh == 0x01)&&(t2_count_ms[T2_COUNTER_S_15] > T2_TIMEOUT_S_15))
	{
		t2_count_ms[T2_COUNTER_S_15] = 0;
		auto_fooh = 0x00;
		CLOSE_RELAY3;
		printf("停止喂水。\r\n");
	}
	if((auto_fooh == 0x02)&&(t2_count_ms[T2_COUNTER_S_10] > T2_TIMEOUT_S_10))
	{
		t2_count_ms[T2_COUNTER_S_10] = 0;
		auto_fooh = 0x00;
		CLOSE_RELAY4;
		printf("停止喂食。\r\n");
	}
}
/**
  * @brief  This function Check status.
  * @param  None
  * @retval : None
  */
void READ_WORKSTATUS(void)
{
	Buff_test = at24c16_read(0x00);
	if((Buff_test == 0x00)||(Buff_test == 0xff))
	{
		driver.mode = 0x00;
	}
	else if(Buff_test == 0x01)
	{
		driver.mode = 0x01;
	}
	else if(Buff_test == 0x02)
	{
		driver.mode = 0x02;
		printf("开始强制清洗，步骤1，延时20秒判断。\r\n");
		driver.step = 0xff;
		t2_count_ms[T2_COUNTER_S_20]  = 0;
	}
	if(driver.mode == 0x00)
	{
		printf("设备在空闲模式。\r\n");
	}
	else if(driver.mode == 0x01)
	{
		printf("设备在工作中。\r\n");
	}
	else if(driver.mode == 0x02)
	{
		printf("设备在强制清洗模式。\r\n");
	}
//	if(READ_LIMIT_SWITCH != 0x00)
//	{
//		meep_status = MEEP_ALWAY_TIME;
//		alarm_start = 1;
//		CLOSE_RELAY2;
//		Delay_ms(500);
//		if(READ_RELAY2 == True)
//		{
//			Uart1.TxBuffer[7] = 0x01;
//			work_fault.BIT3 = 1;
//		}
//		else 
//		{
//			work_fault.BIT3 = 0;
//			Uart1.TxBuffer[7] = 0x00;
//		}
//	}
	if((READ_LIMIT_SWITCH != 0x00)&&(alarm_start == 0))
	{
		meep_status = MEEP_SHORT_TIME;
		alarm_start = 1;
		START_RELAY2;
		Delay_ms(500);
		printf("门在开启状态。\r\n");
		if(READ_RELAY2 == False)
		{
			Uart1.TxBuffer[7] = 0x01;
		}
		else 
		{
			Uart1.TxBuffer[7] = 0x00;
		}
	}
	if((at24c16_read(0x02) != 0x01) && (C322_Config_Success != 2))
	{
			printf("WIFI 模块第一次启动，未配置，进入配置模式！ %d\r\n",at24c16_read(0x02));
			usr_c322 = 0x13;
			test_c322_value = 0;		
	}
	else if(C322_Config_Success != 2)
	{
		printf("WIFI 连接中，等待心跳。\r\n");
		usr_c322 = 0x13;
		test_c322_value = 0x01;
		t2_count_ms[T2_COUNTER_S_60] = 55000;
	}
	else
	{
		printf("AT命令配置wifi开始。\r\n");
	}
	if((alarm_start == 0x01)&&(C322_Config_Success != 0))
	{
			Alarm_Data[2] = id_name[0];
			Alarm_Data[3] = id_name[1];
			Alarm_Data[4] = id_name[2];
			Alarm_Data[5] = id_name[3];
			Alarm_Data[6] = 0x03;
			Alarm_Data[7] = 0x01;
			if(ModbusCrc16_Send(Alarm_Data,sizeof(Alarm_Data)) == True)
			{
				HAL_UART_Transmit(&huart1, Alarm_Data,sizeof(Alarm_Data), UART_Transmit_Timeout);
				printf("未发送指令时，门开启报警。\r\n");
				meep_status = MEEP_SHORT_TIME;
				t2_count_ms[T2_COUNTER_MS_1500] = 0;
			}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
