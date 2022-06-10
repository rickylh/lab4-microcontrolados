#ifndef __UART__
#define __UART__

#include "gpio.h"

void uartInit();
void uartWrite(uint8_t c);
uint8_t uartNotFull();
uint8_t uartHasData();
uint8_t hasData();
uint8_t uartRead();
void uartPrint(char *str);
void uartPrintln(char *str);

#endif // __UART__
