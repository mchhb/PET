#ifndef __24c16_H
#define __24c16_H

#include "stdint.h"
#include "config.h"
#include "main.h"
extern __IO uint32_t time_delay;
void at24c16_init(void);
void at24c16_write(uint16_t addr, unsigned char val);
unsigned char at24c16_read(uint16_t addr);
void eep_block_write(uint16_t eepAddr, uint8_t* dat, uint16_t index, uint16_t len);
void erase_eeprom(uint16_t startAddr, uint16_t len);

void Delay_ms(volatile unsigned long nms);
void Delay_us(volatile unsigned long nus);
#endif /* __MAIN_H */




