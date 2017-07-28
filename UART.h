#ifndef __UART_H
#define __UART_H

#include "stm8s.h"

void init_UART(void); 
void UartPrintf(char *message);
void UartPrintCh(char i);

#endif /* __UART_H */