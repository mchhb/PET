#include "24c16.h"

__IO uint32_t time_delay;

//SysTick实现延时n_ms，中断方式
void Delay_ms(volatile unsigned long nms)
{
    //SYSTICK分频--1ms的系统时钟中断
    if (SysTick_Config(HAL_RCC_GetHCLKFreq()/1000))
    {
   
        while (1);
    }
    time_delay=nms;//读取定时时间
    while(time_delay);
    SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}
 
 
//SysTick实现延时n_us，中断方式
void Delay_us(volatile unsigned long nus)
{
 //SYSTICK分频--1us的系统时钟中断
    if (SysTick_Config(HAL_RCC_GetHCLKFreq()/1000000))
    {
   
        while (1);
    }
    time_delay=nus;//读取定时时间
    while(time_delay);
    SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}
void at24c16_start(void)
{
  SET_EEPROM_SDA_HIGH;
	SET_EEPROM_SCK_HIGH;
	Delay_us(1);
	SET_EEPROM_SDA_LOW;
	SET_EEPROM_SCK_LOW;
}

void at24c16_stop(void)
{
	SET_EEPROM_SDA_LOW;
	SET_EEPROM_SCK_HIGH;
  Delay_us(1);
  SET_EEPROM_SDA_HIGH;
}

void write_1byte(unsigned char val)
{
  unsigned char i, tmp;
  tmp=val;
  
  for (i=0;i<8;i++)
  {
    SET_EEPROM_SCK_LOW;
    Delay_us(1);
    if (((tmp<<i) & 0x80)==0x80)
      SET_EEPROM_SDA_HIGH;
    else
      SET_EEPROM_SDA_LOW;
    Delay_us(1);
    SET_EEPROM_SCK_HIGH;
    Delay_us(1);
  }
  SET_EEPROM_SCK_LOW;
  Delay_us(1);
  SET_EEPROM_SDA_HIGH;
  Delay_us(1);
}


unsigned char read_1byte(void)
{
  unsigned char i,j,k=0;
  
  SET_EEPROM_SCK_LOW;
	Delay_us(1);
	SET_EEPROM_SDA_HIGH;
  for (i=0;i<8;i++)
  {
    Delay_us(1);
    SET_EEPROM_SCK_HIGH;
    Delay_us(1);
    
    if(REAR_EEPORM_SDA==1) j=1; //???SDA becoms inout pin from output pin;
    else j=0;
    k=(k<<1) | j; 
    SET_EEPROM_SCK_LOW;
  }
  Delay_us(1);
  return (k);
}

void clock(void)
{
  uint16_t i=0;
  
  SET_EEPROM_SCK_HIGH;
  Delay_us(1);
  
  while((REAR_EEPORM_SDA==1) && (i<255))
    i++;
  SET_EEPROM_SCK_LOW;
  Delay_us(1);
}

void at24c16_write(uint16_t addr, uint8_t val)
{
   uint8_t l_addr;

  at24c16_start();
  write_1byte(0xa0 | ((addr>>7 & 0xfe)));
  clock();
  l_addr=(addr%256);
  write_1byte(l_addr);
  clock();
  write_1byte(val);
  clock();
  at24c16_stop();
	Delay_ms(5);
}

unsigned char at24c16_read(uint16_t addr)
{
  uint8_t i;
  uint8_t low;
  low = addr & 0x00ff;
  at24c16_start();
  write_1byte(0xa0 | ((addr>>7 & 0xfe)));
  clock();
  write_1byte(low);
  clock();
  at24c16_start();
  write_1byte(0xa1);
  clock();
  i=read_1byte();
  at24c16_stop();
  return(i);
}
//eep block write
//eepAddr: eeprom start address
//dat: data array to be saved to eeprom
//index: data array start index
//len: how long to be write
void eep_block_write(uint16_t eepAddr, uint8_t* dat, uint16_t index, uint16_t len)
{
 	  uint16_t i;
  for(i=0; i<len; i++)
  {
    at24c16_write(eepAddr+i, dat[index+i]);
  }
}

void erase_eeprom(uint16_t startAddr, uint16_t len)
{	  
      uint16_t i;
    for(i=startAddr;i<startAddr+len;i++)
  {
    at24c16_write(i,0xff);
  }
}

