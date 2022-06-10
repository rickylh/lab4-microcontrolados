#ifndef __TIMER__
#define __TIMER__

#include "gpio.h"

void initTimerP200ms();
void initTimerPeriodicouS(uint16_t tempo);
void initTimerPeriodicoS(uint32_t tempo);

#endif // __TIMER__
