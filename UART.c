#include "UART.h"

void init_UART() {
	// PD6 RX -> USB TX
	// PD5 TX -> USB RX
	UART1_DeInit();
	UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,    	UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE); 

	}
	
void UartPrintf(char *message)
{
	//char *ch = message;
	while (*message)
	{
			UART1->DR = (unsigned char) (*message);		// put char into a buffer
			while ((UART1->SR & (unsigned char) UART1_FLAG_TXE) == RESET);	// wait end of transmission
			message++;																// next symbol transmission
	}
}

void UartPrintCh(char i)
{
	UART1->DR = (unsigned char) (i);		// put char into a buffer
	while ((UART1->SR & (unsigned char) UART1_FLAG_TXE) == RESET);	// wait end of transmission

}