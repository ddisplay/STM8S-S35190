/**

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

#include "stm8s.h"

//void delay_1us(u16 n_1us);
//void delay_ms(u16 n_ms);
void delay_software(volatile uint32_t count);
void delay(volatile uint32_t count);

#endif /* __DELAY_H*/