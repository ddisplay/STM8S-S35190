#include "S35190.h"

/*
This is a fork of Faithsws RTC library.
https://github.com/faithsws
*/

extern unsigned char data_RX[7];
extern unsigned char data_TX[7];

void init_S35190(void)
{
  //GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST)
	GPIO_Init(S35190_DATA_PORT, (GPIO_Pin_TypeDef)S35190_DATA, GPIO_MODE_OUT_OD_LOW_FAST); 
  GPIO_Init(S35190_RST_PORT, (GPIO_Pin_TypeDef)S35190_RST, GPIO_MODE_OUT_PP_HIGH_FAST); 
  GPIO_Init(S35190_SCLK_PORT, (GPIO_Pin_TypeDef)S35190_SCLK, GPIO_MODE_OUT_PP_HIGH_FAST); 
}
 void sclk(char state)
{
  if(state)
    GPIO_WriteHigh(S35190_SCLK_PORT,S35190_SCLK);
  else
    GPIO_WriteLow(S35190_SCLK_PORT,S35190_SCLK);
}
 void data_out(char state)
{
  GPIO_Init(S35190_DATA_PORT, (GPIO_Pin_TypeDef)S35190_DATA, GPIO_MODE_OUT_OD_LOW_FAST); 
  if(state)
    GPIO_WriteHigh(S35190_DATA_PORT,S35190_DATA);
  else
    GPIO_WriteLow(S35190_DATA_PORT,S35190_DATA);
}
 BitStatus data_in(void)
{
  GPIO_Init(S35190_DATA_PORT, (GPIO_Pin_TypeDef)(S35190_DATA ), GPIO_MODE_IN_FL_NO_IT);
  return GPIO_ReadInputPin(S35190_DATA_PORT,(GPIO_Pin_TypeDef)(S35190_DATA ));
}
 void rst(char state)
{
  if(state)
    GPIO_WriteHigh(S35190_RST_PORT,S35190_RST);
  else
    GPIO_WriteLow(S35190_RST_PORT,S35190_RST);
}
 void write_byte(unsigned char data)
{
  unsigned char i;
  for(i = 0;i<8;i++)
  {
    sclk(0);
    if(data & 0x01)
      data_out(1);
    else
      data_out(0);
    data = data>>1;
    sclk(1);
  }
}

// Write address and number of bytes
void write_timer(unsigned char Addr, unsigned char Nbyte)
{
  unsigned char i;
  rst(0);
  sclk(1);
  rst(1);
  write_byte(0|Addr|S35190_FCODE);// 0110 - fcode, C2C1C0-command, R/W FFFFCCCR
  for(i = 0;i<Nbyte;i++)					
  {
		write_byte(data_TX[i]);
  }
  sclk(1);
  rst(0);	
  data_out(1);
}

 unsigned char read_byte(void)
{
  unsigned char i,temp = 0;
  BitStatus bit;
  for(i = 0;i<8;i++)
  {
		sclk(0);
		temp = temp>>1;		
    bit = data_in();
		if(bit != RESET)
    {
    temp = temp | 0x80;  
    }
		sclk(1);
  }
  return temp; 
}

// Read address and number of bytes
void read_timer(unsigned char Addr, unsigned char Nbyte)	
{
  unsigned char i;
  rst(0);
  sclk(1);
  rst(1);
	write_byte(0x80|Addr|S35190_FCODE);		// 1 Read
  for(i = 0;i<Nbyte;i++)								
  {
		data_RX[i] = read_byte();
  }
	sclk(1);
	rst(0);
  data_out(1);
}


