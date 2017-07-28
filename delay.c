#include "delay.h"

uint32_t TimingDelay = 0;


void delay_software(volatile uint32_t count) {
for ( ; count > 0; --count);
}

void delay(volatile uint32_t nTime)
{
  TimingDelay = nTime;

  while (TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
