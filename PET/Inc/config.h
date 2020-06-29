#ifndef __CONFIG_H
#define __CONFIG_H

#include "stdint.h"
/************************/

#define UART_Transmit_Timeout			0xffff
#define True											1
#define False											0
/************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif


typedef struct
{
	uint8_t mode;
	uint8_t status;
	uint8_t step;
}Driver;
typedef struct
{
	volatile uint8_t aRxBuffer;				
	uint8_t RxBuff[255];		
	volatile uint8_t Rx_Cnt;		
	uint8_t ReceiveSuccess_Flag;
	uint8_t Flag;
	uint8_t RxBuffer[10];
	uint8_t TxBuffer[10];
}USART;

union u8_u{
  uint8_t  b;
  struct {
   uint8_t BIT0 : 1;
   uint8_t BIT1 : 1;
   uint8_t BIT2 : 1;
   uint8_t BIT3 : 1;
   uint8_t BIT4 : 1;
   uint8_t BIT5 : 1;
   uint8_t BIT6 : 1;
   uint8_t BIT7 : 1;
  };   
};

typedef union u8_u us8_t;
/************************/

#define MEEP_SHORT_TIME						0x01
#define MEEP_ALWAY_TIME						0x03
#define MEEP_CLOSE								0x05

/************************/

/************************/

#define USR_C322_RESET									0x00
#define USR_C322_UART										0x01
#define USR_C322_RECEIVE								0x02
#define	USR_C322_CONFIG									0x03
#define	USR_C322_OK											0x04
#define USR_C322_MODE										0x05
#define USR_C322_ROUTER									0x07
#define USR_C322_DHCP										0x09
#define USR_C322_CONNECT_ROUTER_STATUS	0x0B
#define USR_C322_ROUTER_STATUS					0x0C
#define USR_C322_SERIALAPP							0x0D
#define USR_C322_SERVER									0x0F
#define USR_C322_WORK										0x11
#define USR_C322_ENTM_OK								0x12
#define USR_C322_ERROR 									0xff
#define USR_C322_RECEIVE_LENGTH					0x0a
/************************/

/************************/

#define Noise_Data_Length									7
#define Para_Data_Length									10
/************************/

/************************/
// unit is 1ms
#define T2_MS_ARRAY_NUM  		19
#define T2_TIMEOUT_MAXIMUM		350000

#define T2_COUNTER_MS_200			0
#define T2_COUNTER_MS_500			1
#define T2_COUNTER_S_1				2
#define T2_COUNTER_S_2				3
#define T2_COUNTER_S_5				4
#define T2_COUNTER_S_10				5
#define T2_COUNTER_S_20				6
#define T2_COUNTER_S_9				7
#define T2_COUNTER_S_60				8
#define T2_COUNTER_S_30				9
#define T2_COUNTER_S_6				10
#define T2_COUNTER_MS_1500		11
#define T2_COUNTER_S_8				12
#define T2_COUNTER_S_35				13
#define T2_COUNTER_S_15				14
#define T2_COUNTER_S_2_300			15
#define T2_COUNTER_S_300			16
#define T2_COUNTER_S_2_60			17
#define T2_COUNTER_S_2_30			18

#define T2_TIMEOUT_MS_200			200
#define T2_TIMEOUT_MS_500			500
#define T2_TIMEOUT_S_1				1000
#define T2_TIMEOUT_S_2				2000
#define T2_TIMEOUT_S_5				5000
#define T2_TIMEOUT_S_10				10000

#define T2_TIMEOUT_S_20				20000
#define T2_TIMEOUT_S_9				9000
#define T2_TIMEOUT_S_60				60000
#define T2_TIMEOUT_S_30				30000
#define T2_TIMEOUT_S_6				6000
#define T2_TIMEOUT_MS_1500		1500
#define T2_TIMEOUT_S_8				8000
#define T2_TIMEOUT_S_35				35000
#define T2_TIMEOUT_S_15				15000
#define T2_TIMEOUT_S_2_300		300000
#define T2_TIMEOUT_S_300			300000
#define T2_TIMEOUT_S_2_60			60000
#define T2_TIMEOUT_S_2_30			30000
/************************/

/************************/
/*				OUTPUT				*/
//
#define CLOSE_MEEP 				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)
#define START_MEEP 				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)
//
#define CLOSE_RELAY1 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET)
#define START_RELAY1 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET)
//
#define CLOSE_RELAY2 			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)
#define START_RELAY2 			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET)
//
#define CLOSE_RELAY3 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET)
#define START_RELAY3 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)
//
#define CLOSE_RELAY4 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET)
#define START_RELAY4 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET)
//
#define CLOSE_RELAY5 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET)
#define START_RELAY5 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET)
//
#define CLOSE_RELAY6 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)
#define START_RELAY6 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
//
#define CLOSE_RELAY7 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)
#define START_RELAY7 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)
//
#define CLOSE_RELAY8 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)
#define START_RELAY8 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)

#define CLOSE_RELAY9 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)
#define START_RELAY9 			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)

#define CLOSE_RELAY10 		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)
#define START_RELAY10 		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)

/************************/

/************************/
//LED
#define CLOSE_LED1 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET)
#define START_LED1 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)

#define CLOSE_LED2 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET)
#define START_LED2 			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET)

#define CLOSE_LED3 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)
#define START_LED3 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)

#define CLOSE_LED4 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)
#define START_LED4 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)

/************************/
/*			INPUT	 					*/
//RELAY
#define READ_RELAY1 				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
#define READ_RELAY2 				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)
#define READ_RELAY3 				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_12)
#define READ_RELAY4 				HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define READ_RELAY5 				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)
#define READ_RELAY6 				HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)
#define READ_RELAY7 				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)
#define READ_RELAY8 				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
#define READ_RELAY9 				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)
//HC_SR505_OUT
#define READ_HC_SR505_OUT1	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)
#define READ_HC_SR505_OUT2	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)
#define READ_HC_SR505_OUT3	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)
//LIMIT SWITCH
#define READ_LIMIT_SWITCH		HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)
/************************/

/************************/
//24C16 CONFIG
#define SET_EEPROM_SDA_HIGH		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET) 
#define SET_EEPROM_SDA_LOW		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET) 
#define REAR_EEPORM_SDA				HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)
#define SET_EEPROM_SCK_HIGH		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET) 
#define SET_EEPROM_SCK_LOW		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET) 
/************************/

/************************/
#define WORK_FREE						0x00
#define WORK_NORMAL					0x01
#define WORK_ERROR					0x04
#define WORK_UNUSUAL				0x03
#define WORK_CLOSE					0x02

/************************/

/************************/

#define NOISE_ALARM					0x46

/************************/


#endif
