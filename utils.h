#ifndef __UTILS__
#define __UTILS__

#include "tm4c1294ncpdt.h"
#include <stdint.h>

void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);
void SysTick_Wait1us(uint32_t delay);

#endif // __UTILS__
