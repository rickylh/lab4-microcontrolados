#include "timer.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>

// Inicializa o timer2 como periodico de 200ms
void initTimerP200ms() {
    // Ativar o clock para o timer2
    SYSCTL_RCGCTIMER_R = SYSCTL_RCGCTIMER_R | 0x4;
    while ((SYSCTL_PRTIMER_R & (0x4)) != 0x4) // Verificar se o clock esta ativo
        ;
    TIMER2_CTL_R &= ~0x1;      // Desabilitar o timer2
    TIMER2_CFG_R &= ~0x7;      // Modo de 32 bits
    TIMER2_TAMR_R |= 0x2;      // Modo periodico
    TIMER2_TAILR_R = 15999999; // Contagem = 15999999
    TIMER2_TAPR_R = 0;         // Sem prescale
    TIMER2_ICR_R |= 0x1;       // ACK da interrupção
    TIMER2_IMR_R |= 0x1;       // Utilizar interrupção para estouro do timer2A
    NVIC_PRI5_R = 0x4 << 29; // Setar prioridade 4 para interrupção no timer2A
    NVIC_EN0_R = (uint32_t)(1 << 23); // Habilitar a interrupção para o timer2A
    TIMER2_CTL_R |= 0x1;              // Habilitar o timer2
}

// Inicializa o timer2 como periodico com tempo em us até 819uS
void initTimerPeriodicouS(uint16_t tempo) {
    int count = tempo * 1e-6 * 80e6 - 1;
    // Ativar o clock para o timer2
    SYSCTL_RCGCTIMER_R = SYSCTL_RCGCTIMER_R | 0x4;
    while ((SYSCTL_PRTIMER_R & (0x4)) != 0x4) // Verificar se o clock esta ativo
        ;
    TIMER2_CTL_R &= ~0x1;    // Desabilitar o timer2
    TIMER2_CFG_R &= ~0xB;    // Modo de 16 bits
    TIMER2_TAMR_R |= 0x2;    // Modo periodico
    TIMER2_TAILR_R = count;  // Contagem = count
    TIMER2_TAPR_R = 0;       // Sem prescale
    TIMER2_ICR_R |= 0x1;     // ACK da interrupção
    TIMER2_IMR_R |= 0x1;     // Utilizar interrupção para estouro do timer2A
    NVIC_PRI5_R = 0x0 << 29; // Setar prioridade 4 para interrupção no timer2A
    NVIC_EN0_R = (uint32_t)(1 << 23); // Habilitar a interrupção para o timer2A
    TIMER2_CTL_R |= 0x1;              // Habilitar o timer2
}

// Inicializa o timer2 como periodico com tempo em us até 53.68s
void initTimerPeriodicoS(uint32_t tempo) {
    int count = tempo * 1e-6 * 80e6 - 1;
    // Ativar o clock para o timer2
    SYSCTL_RCGCTIMER_R = SYSCTL_RCGCTIMER_R | 0x4;
    while ((SYSCTL_PRTIMER_R & (0x4)) != 0x4) // Verificar se o clock esta ativo
        ;
    TIMER2_CTL_R &= ~0x1;    // Desabilitar o timer2
    TIMER2_CFG_R &= ~0x7;    // Modo de 32 bits
    TIMER2_TAMR_R |= 0x2;    // Modo periodico
    TIMER2_TAILR_R = count;  // Contagem = count
    TIMER2_TAPR_R = 0;       // Sem prescale
    TIMER2_ICR_R |= 0x1;     // ACK da interrupção
    TIMER2_IMR_R |= 0x1;     // Utilizar interrupção para estouro do timer2A
    NVIC_PRI5_R = 0x0 << 29; // Setar prioridade 4 para interrupção no timer2A
    NVIC_EN0_R = (uint32_t)(1 << 23); // Habilitar a interrupção para o timer2A
    TIMER2_CTL_R |= 0x1;              // Habilitar o timer2
}
