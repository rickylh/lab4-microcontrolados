#include "uart.h"

#include "tm4c1294ncpdt.h"
#include <stdint.h>

void uartInit() {
    // 1. Habilitar clock na UART0
    SYSCTL_RCGCUART_R = 0x01;

    // Esperar habilitar o clock da UART0
    while ((SYSCTL_PRUART_R & 0x01) != 0x01)
        ;
    // 2. Desabilitar a UART (limpar o bit0 -> UARTEN)
    UART0_CTL_R &= ~0x1;

    // 3. Escrever o bound-rate 19200 para clock de 80MHz
    UART0_IBRD_R = 260;
    UART0_FBRD_R = 27;

    // 4. Configurar número de bits, paridade, stop bits e fila
    // 8 bits, fila habilitada, paridade impar, verifica paridade, 1 stop bit
    UART0_LCRH_R = 0x72; // 11 1 0 01 0

    // 5. Usar o clock do sistema como clock do UART
    UART0_CC_R = 0;

    // 6. Habilitar o transmissor e receptor e UARTEN
    UART0_CTL_R |= 0x301;

    // 7a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTA);
    // 7b.  após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTA)) != (GPIO_PORTA)) {
    };

    // 8. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTA_AHB_AMSEL_R = 0x00;

    // 9. Habilitar PCTL para selecionar função alternativa U0Rx e U0Tx
    GPIO_PORTA_AHB_PCTL_R |= 0x11;

    // 10. Habilitar a função alternativa nos bit0 e bit1 do AFSEL
    GPIO_PORTA_AHB_AFSEL_R |= 0x03;

    // 11. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTA_AHB_DEN_R |= 0x3; // Bit0 e Bit1
}

void uartWrite(uint8_t c) {
    while ((UART0_FR_R & 0x20) == 0x20)
        ;
    UART0_DR_R = c;
}

uint8_t uartNotFull() {
    return (UART0_FR_R & 0x20) != 0x20;
}

uint8_t uartHasData() {
    return (UART0_FR_R & 0x10) != 0x10;
}

uint8_t uartRead() {
    while ((UART0_FR_R & 0x10) == 0x10)
        ;
    return UART0_DR_R;
}

void uartPrint(char *str) {
    while (*str != 0) {
        uartWrite(*(str++));
    }
}

void uartPrintln(char *str) {
    uartPrint(str);
    uartWrite('\r');
    uartWrite('\n');
}
