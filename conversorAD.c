#include "conversorAD.h"
#include "lcd.h"
#include "tm4c1294ncpdt.h"
#include "utils.h"
#include <stdint.h>

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnop"
                 "qrstuvwxyz"[35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0)
        *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void initConversorAD() {
    // 6. Habilitar o clock no módulo ADC no registrador
    SYSCTL_RCGCADC_R = 0x1;
    while ((SYSCTL_PRADC_R & 0x01) != 0x01) {
    }

    // 7. Setar a maxima taxa de amostragem
    ADC0_PC_R = 0x7;

    // 8. Configurar a prioridade de cada um dos sequenciadores
    // 0 para SS3
    // 1 para SS2
    // 2 para SS1
    // 3 para SS0
    ADC0_SSPRI_R = 0x0123;

    // 9. Desabilitar o sequenciador SS3 para configula-lo
    ADC0_ACTSS_R = 0x00;

    // 10. Configurar o tipo de gatilho 'processor'
    ADC0_EMUX_R = 0x0;

    // 11. Configurar AIN9 como fonte de entrada analogica no registrador
    ADC0_SSMUX3_R = 0x9;

    // 12. Configurar os bits IE0 e END0 de controle no nibble
    // para habilitar o sinal de interrupção e habilitar se a
    // amostra é fim de sequencia
    ADC0_SSCTL3_R = 0x6;

    // 13. Setar o bit correspondente para configurar interrupção
    // ADC0_IM_R = 0x8;

    // 14. Habilitar o sequenciador SS3
    ADC0_ACTSS_R = 0x8;
}

uint16_t readPot() {
    // Iniciar o gatilho de SW
    ADC0_PSSI_R = 0x8;

    // Polling do registrador para sequenciador SS3
    while ((ADC0_RIS_R & 0x8) != 0x8) {
    }
    int value = ADC0_SSFIFO3_R;

    // Realizar o ACK no registrador para sequenciador SS3
    ADC0_ISC_R = 0x8;
    return value;
}
