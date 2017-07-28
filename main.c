#include "main.h"
#include "stm8s.h"
#include "delay.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include "S35190.h"

/*
V0.2	S35190 @ STM8S003F3U6TR

http://dotdisplay.blogspot.com/

*/ 


unsigned char data_RX[14] = {0,1,2,3,4,5,6};
//unsigned char data_TX[7] = {0x23,0x58,0x59,27,7,5,13};
unsigned char data_TX[7] = {0x02,0x03,0x04,0,0,0,0};		
unsigned char Display[14] = {0,0,0,0,0,0,0};
unsigned char hour, min, sec, dot;	
unsigned char i = 0, j = 0;

main()
{
	
	CLK_HSIPrescalerConfig(CLK_PRESCALER_CPUDIV1);	// 16MHz
	init_gpio();	
	init_UART(); 
	init_S35190();

  disableInterrupts();

/*	
	//3 bytes config, time only
	data_TX[0] = 0b00000010;		//config byte st1, B7=1(reset) B6=1 (24H mode)
	write_timer(S35190_ST1,1); 

	data_TX[0] = 0x23;					//time setup 23 hours 24H mode
	data_TX[1] = 0x59;					//time setup 59 min 24H mode
	data_TX[2] = 0x45;					//time setup 45 sec 24H mode
  write_timer(S35190_HMS,3); 
*/	

	data_TX[0] = 0b00000000;		//config byte st1, B7=1(reset) B6=0 (12H mode)
	write_timer(S35190_ST1,1); 

	data_TX[0] = 0b11111100;		//Time correction +16s day
	//data_TX[0] = 0b00000010;		//Time correction -16s day
	write_timer(S35190_COR,1); 
/*
	//3 bytes config
	data_TX[0] = 0x11|0x40;			//time setup 11 hours 12H mode, 0x40 - PM, 0x00 - AM,
	data_TX[1] = 0x59;					//time setup 59 min 12H mode
	data_TX[2] = 0x45;					//time setup 45 sec 12H mode
  write_timer(S35190_HMS,3); 
*/
	data_TX[0] = 0x17;					//time setup Year
	data_TX[1] = 0x12;					//time Month
	data_TX[2] = 0x31;					//time Day
	data_TX[3] = 0x06;					//time Week Day (Sunday)
	data_TX[4] = 0x11|0x40;			//time setup 11 hours 12H mode, 0x40 - PM, 0x00 - AM,
	data_TX[5] = 0x59;					//time setup 59 min 12H mode
	data_TX[6] = 0x53;					//time setup 45 sec 12H mode
  write_timer(S35190_YMS,7); 

	while (1){
/*
	//3 bytes config
	read_timer(S35190_HMS,3);
	//data_RX[0] = data_RX[0] & 0b00111111; // skip AM/PM ,alarm bit, 24H mode
	data_RX[0] = data_RX[0] & 0b01111111; //  skip alarm bit, 12H mode
	if ((data_RX[0] & 0b00111111) == 0x00){
	data_RX[0] = 0x12;										// 12 hours nonexisting data, p.23 datasheet
	}
	
	Display[H_H] = data_RX[0] >> 4;				//hours
	Display[H_L] = data_RX[0] & 0x0f;
	Display[M_H] = data_RX[1] >> 4;				//mins
	Display[M_L] = data_RX[1] & 0x0f;
	Display[S_H] = data_RX[2] >> 4;				//sec
	Display[S_L] = data_RX[2] & 0x0f;
*/


	read_timer(S35190_YMS,7);
	//data_RX[0] = data_RX[0] & 0b00111111; // skip AM/PM ,alarm bit, 24H mode
	data_RX[4] = data_RX[4] & 0b00111111; //  skip alarm bit, skip PM bit 12H mode
	if ((data_RX[4] & 0b00111111) == 0x00){
	data_RX[4] = 0x12;										// 12 hours nonexisting data, p.23 datasheet
	}

	Display[H_H] = data_RX[0] >> 4;				//YY
	Display[H_L] = data_RX[0] & 0x0f;
	Display[M_H] = data_RX[1] >> 4;				//MM
	Display[M_L] = data_RX[1] & 0x0f;
	Display[S_H] = data_RX[2] >> 4;				//DD
	Display[S_L] = data_RX[2] & 0x0f;

	Display[6] = data_RX[3] >> 4;				//Week DD
	Display[7] = data_RX[3] & 0x0f;

	Display[8] = data_RX[4] >> 4;				//hours
	Display[9] = data_RX[4] & 0x0f;
	Display[10] = data_RX[5] >> 4;				//mins
	Display[11] = data_RX[5] & 0x0f;
	Display[12] = data_RX[6] >> 4;				//sec
	Display[13] = data_RX[6] & 0x0f;
	
	GPIO_WriteReverse(LED1_GPIO_PORT, LED_Y);		//Low LED On, High Off 
	GPIO_WriteReverse(LED2_GPIO_PORT, LED_B);		//Low LED Off, High On 

	delay_software(55000);	//12.64mS

	
	for (i = 0; i < 14; i++){
	UartPrintCh(Display[i]+(0x30));
	//UartPrintCh(data_RX[i]+(0x30));
	}	
	UartPrintCh(' ');	
	UartPrintf("\r\n"); 

	
	}
}


