// lcd.c
// Desenvolvido para a placa EK-TM4C1294XL

#include "lcd.h"
#include "utils.h"

void LCD_init(void) {
    LCD_GPIO_Init();
    // Inicia Configuracao do lcd, modo de 8 bits, 2 linhas
    LCD_enviarComando(0x38, 1640);

    // Cursor com auto incremento para direita
    LCD_enviarComando(0x06, 40);

    // Inicia Configuracao do cursor, habilita cursor e display e
    // cursor não pisca
    LCD_enviarComando(0x0E, 40);
    // LCD_enviarComando(0x01, 1640);
    LCD_enviarComando(0x01, 1640);
}

void LCD_enviarComando(uint8_t comando, uint32_t delay) {
    // Escreve na porta K o comando de R0
    PortK_Output(comando);
    PortM_Output(0x04);     // RS = 0, RW = 0, RE = 1
    SysTick_Wait1us(20);    // Esperar 10us
    PortM_Output(0x00);     // RS = 0, RW = 0, RE = 0
    SysTick_Wait1us(delay); // Esperar 10us
}

void LCD_enviarDado(uint8_t dado) {
    // Escreve na porta K o comando de R0
    PortK_Output(dado);
    PortM_Output(0x05);  // RS = 1, RW = 0, RE = 1
    SysTick_Wait1us(10); // Esperar 10us
    PortM_Output(0x00);  // RS = 0, RW = 0, RE = 0
    SysTick_Wait1us(40); // Esperar 40us
}

void LCD_reset(void) {
    LCD_enviarComando(0x01, 1640);
}

void LCD_moveCursor(uint8_t linha, uint8_t pos) {
    if (linha == 1) {
        LCD_enviarComando(0x80 + pos, 40);
    } else if (linha == 2) {
        LCD_enviarComando(0xC0 + pos, 40);
    }
}

void LCD_print_reset(char *linha1, char *linha2) {
    LCD_reset(); // Limpar o display e ir para primeira linha
    LCD_print(linha1);
    LCD_enviarComando(0xC0, 40); // Pular para inicio da segunda linha
    LCD_print(linha2);
}

void LCD_print(char *linha) {
    // Percorre a linha e imprime os digitos
    for (char c = *linha; c != '\0'; c = *(++linha)) {
        LCD_enviarDado(c);
    }
}
