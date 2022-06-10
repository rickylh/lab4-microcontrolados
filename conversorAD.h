#ifndef __CONVERSOR_AD__
#define __CONVERSOR_AD__

#include "gpio.h"

void initConversorAD();
uint16_t readPot();
char *itoa(int value, char *result, int base);

#endif // __CONVERSOR_AD__
