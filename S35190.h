#ifndef __S35190_H
#define __S35190_H

#include "stm8s.h"
#include "stm8s_gpio.h"
#include "delay.h"

#define S35190_FCODE			0b00000110		//IC Fixed code Address 
#define S35190_YMS				0b00100000		//C2C1C0 011 time data2
#define S35190_HMS				0b01100000		//C2C1C0 011 time data2
#define S35190_COR				0b00110000		//C2C1C0 110 Clock correction
#define S35190_ST1				0b00000000		//C2C1C0 011 status reg1 

#define S35190_DATA_PORT  (GPIOB)				// port
#define S35190_DATA  			GPIO_PIN_5  	// IO

#define S35190_RST_PORT  (GPIOD)				// port
#define S35190_RST  			GPIO_PIN_2  	// CS

#define S35190_SCLK_PORT  (GPIOD)				// port
#define S35190_SCLK  			GPIO_PIN_3		// CLK


void init_S35190(void); 
void sclk(char h);
void data_out(char h);
BitStatus data_in(void);
void rst(char h);
void write_byte(unsigned char data);
unsigned char read_byte(void);
void write(unsigned char  addr,unsigned char data);
unsigned char read(unsigned char addr);
void write_timer(unsigned char Addr, unsigned char Nbyte);
void read_timer(unsigned char Addr, unsigned char Nbyte);	


#endif /* S35190 */