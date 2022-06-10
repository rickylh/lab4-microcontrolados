// lcd.h
// Desenvolvido para a placa EK-TM4C1294XL

#ifndef __LCD__
#define __LCD__

#include "gpio.h"

// Inicializar o display
void LCD_init(void);

// Enviar um comando para o display
void LCD_enviarComando(uint8_t comando, uint32_t delay);

// Enviar um dado para o display
void LCD_enviarDado(uint8_t dado);

// Limpar o display e imprimir a linha1 na primeira linha do display e a linha2
// na segunda linha do display
void LCD_print_reset(char *linha1, char *linha2);

// Imprimir uma string no display a partir da posição atual do cursor
void LCD_print(char *linha);

// Limpar o display e ir para primeira linha
void LCD_reset(void);

// Move o cursor para posicão na linha indicada
// Parâmetro de entrada: linha: 1 ou 2
//                         pos: [0, 15]
// Parâmetro de saída: não tem
void LCD_moveCursor(uint8_t linha, uint8_t pos);

#endif // __LCD__
