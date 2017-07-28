#ifndef __GPIO_H
#define __GPIO_H

#include "stm8s_gpio.h"

/*
HDSP2000 Test
*/

#define Scan_GPIO_PORT  (GPIOC)			// Scan port
#define C1  			GPIO_PIN_7  			// Col1
#define C2  			GPIO_PIN_6  			// Col2
#define C3  			GPIO_PIN_5  			// Col3
#define C4  			GPIO_PIN_4  			// Col4
#define C5  			GPIO_PIN_3  			// Col5
#define Scan_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)


#define Control1_GPIO_PORT  (GPIOD)	// HDSP2000 control 
#define IN_  			GPIO_PIN_4  			// IN
#define CLK_ 			GPIO_PIN_5  			// CLK
#define Control1_GPIO_PINS  (GPIO_PIN_4 | GPIO_PIN_5)

#define Control2_GPIO_PORT  (GPIOA)	// HDSP2000 control 
#define VB  			GPIO_PIN_3  			// VB Blank control
#define Control2_GPIO_PINS  (GPIO_PIN_3)

#define LED1_GPIO_PORT  (GPIOB)				// 
#define LED_Y  			GPIO_PIN_4  			// LED yellow (D2)
#define LED1_GPIO_PINS  (GPIO_PIN_4)

#define LED2_GPIO_PORT  (GPIOD)			// 
#define LED_B			GPIO_PIN_1  			// LED blue (D4)
#define LED2_GPIO_PINS  (GPIO_PIN_1)


#define Adc_GPIO_PORT  (GPIOD)				// ADC port	PORTD 6, buttons
#define Adc_GPIO_PINS  (GPIO_PIN_6)


void init_gpio(void);


#endif /* __GPIO_H */