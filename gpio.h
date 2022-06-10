// gpio.h
// Desenvolvido para a placa EK-TM4C1294XL

#ifndef __GPIO__
#define __GPIO__

#include "tm4c1294ncpdt.h"
#include <stdint.h>

#define GPIO_PORTA (0x0001)
#define GPIO_PORTB (0x0002)
#define GPIO_PORTC (0x0004)
#define GPIO_PORTD (0x0008)
#define GPIO_PORTE (0x0010)
#define GPIO_PORTF (0x0020)
#define GPIO_PORTG (0x0040)
#define GPIO_PORTH (0x0080)
#define GPIO_PORTJ (0x0100)
#define GPIO_PORTK (0x0200)
#define GPIO_PORTL (0x0400)
#define GPIO_PORTM (0x0800)
#define GPIO_PORTN (0x1000)
#define GPIO_PORTP (0x2000)
#define GPIO_PORTQ (0x4000)

// -------------------------------------------------------------------------------
// Função GPIO_Init
// Inicializa os ports J e N
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função Teclado_GPIO_Init
// Inicializa os ports L e M
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void Teclado_GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função LCD_GPIO_Init
// Inicializa os ports M e K
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void LCD_GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função LEDS_GPIO_Init
// Inicializa os ports A, Q e P
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void LEDS_GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função Motor_GPIO_Init
// Inicializa o port H
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void Motor_GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função Pot_GPIO_Init
// Inicializa o port H
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void Pot_GPIO_Init(void);

// -------------------------------------------------------------------------------
// Função PortN_Output
// Escreve os valores no port N
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortN_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortA_Output
// Escreve os valores no port A
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortA_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortB_Output
// Escreve os valores no port B
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortB_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortQ_Output
// Escreve os valores no port Q
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortQ_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortK_Output
// Escreve os valores no port K
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortK_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortE_Output
// Escreve os valores no port E
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortE_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortF_Output
// Escreve os valores no port F
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortF_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortH_Output
// Escreve os valores no port H
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortH_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortM_Output
// Escreve os valores no port M
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortM_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortL_Output
// Escreve os valores no port L
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortL_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortP_Output
// Escreve os valores no port P
// Parâmetro de entrada: Valor a ser escrito
// Parâmetro de saída: não tem
void PortP_Output(uint32_t valor);

// -------------------------------------------------------------------------------
// Função PortM_Input
// Lê os valores de entrada do port M
// Parâmetro de entrada: Não tem
// Parâmetro de saída: o valor da leitura do port
uint32_t PortM_Input(void);

// -------------------------------------------------------------------------------
// Função PortJ_Input
// Lê os valores de entrada do port J
// Parâmetro de entrada: Não tem
// Parâmetro de saída: o valor da leitura do port
uint32_t PortJ_Input(void);

// -------------------------------------------------------------------------------
// Função PortL_Input
// Lê os valores de entrada do port L
// Parâmetro de entrada: Não tem
// Parâmetro de saída: o valor da leitura do port
uint32_t PortL_Input(void);

// -------------------------------------------------------------------------------
// Função PortM_ConfigDir
// Parâmetro de entrada: R0 --> se o BIT4-7 é saida ou não
// Parâmetro de saída: Não tem
void PortM_ConfigDir(uint8_t saida);

// -------------------------------------------------------------------------------
// Função PortJ_Init
// Inicializa interrupção para a chave na port J0
// Parâmetro de entrada: Não tem
// Parâmetro de saída: Não tem
void PortJ_Init(void);
#endif // __GPIO__
