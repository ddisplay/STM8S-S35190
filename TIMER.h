#ifndef __TIMER_H
#define __TIMER_H

#include "stm8s.h"

//#define TIM4_PERIOD       124			// for 1mS
#define TIM4_PERIOD       8					// for 71uS

void init_timer(void);


#endif /* __TIMER_H */