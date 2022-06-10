// gpio.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa as portas J e N
// Prof. Guilherme Peron

#include "gpio.h"

void GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTJ | GPIO_PORTN | GPIO_PORTF);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTJ | GPIO_PORTN | GPIO_PORTF)) !=
           (GPIO_PORTJ | GPIO_PORTN | GPIO_PORTF)) {
    };

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTF_AHB_AMSEL_R = 0x00;
    GPIO_PORTJ_AHB_AMSEL_R = 0x00;
    GPIO_PORTN_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTF_AHB_PCTL_R = 0x00;
    GPIO_PORTJ_AHB_PCTL_R = 0x00;
    GPIO_PORTN_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTF_AHB_DIR_R |= 0x011; // BIT0 | BIT4
    GPIO_PORTJ_AHB_DIR_R |= 0x00;
    GPIO_PORTN_DIR_R |= 0x03; // BIT0 | BIT1

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTF_AHB_AFSEL_R = 0x00;
    GPIO_PORTJ_AHB_AFSEL_R = 0x00;
    GPIO_PORTN_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTF_AHB_DEN_R |= 0x11; // Bit0 e bit4
    GPIO_PORTJ_AHB_DEN_R |= 0x03; // Bit0 e bit1
    GPIO_PORTN_DEN_R |= 0x03;     // Bit0 e bit1

    // 7. Habilitar resistor de pull-up interno, setar PUR para 1
    GPIO_PORTJ_AHB_PUR_R = 0x03; // Bit0 e bit1
}

void Teclado_GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTM | GPIO_PORTL);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTM | GPIO_PORTL)) !=
           (GPIO_PORTM | GPIO_PORTL)) {
    };

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTL_AMSEL_R = 0x00;
    GPIO_PORTM_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTL_PCTL_R = 0x00;
    GPIO_PORTM_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTL_DIR_R &= ~0x0F; // Bit0-3
    GPIO_PORTM_DIR_R |= 0xF0;  // Bit4-7

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTL_AFSEL_R = 0x00;
    GPIO_PORTM_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTL_DEN_R |= 0x0F; // Bit0-3
    GPIO_PORTM_DEN_R |= 0xF0; // Bit4-7

    // 7. Habilitar resistor de pull-up interno, setar PUR para 1
    GPIO_PORTL_PUR_R = 0x0F; // Bit0-3
    GPIO_PORTM_PUR_R = 0xF0; // Bit0 e bit1
}

void LEDS_GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTA | GPIO_PORTQ | GPIO_PORTP);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTA | GPIO_PORTQ | GPIO_PORTP)) !=
           (GPIO_PORTA | GPIO_PORTQ | GPIO_PORTP)) {
    };

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTA_AHB_AMSEL_R = 0x00;
    GPIO_PORTQ_AMSEL_R = 0x00;
    GPIO_PORTP_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTA_AHB_PCTL_R = 0x00;
    GPIO_PORTQ_PCTL_R = 0x00;
    GPIO_PORTP_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTA_AHB_DIR_R |= 0xF0; // Bit4-7
    GPIO_PORTQ_DIR_R |= 0x0F;     // Bit0-3
    GPIO_PORTP_DIR_R |= 0x20;     // Bit5

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTA_AHB_AFSEL_R = 0x00;
    GPIO_PORTQ_AFSEL_R = 0x00;
    GPIO_PORTP_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTA_AHB_DEN_R |= 0xF0; // Bit4-7
    GPIO_PORTQ_DEN_R |= 0x0F;     // Bit0-3
    GPIO_PORTP_DEN_R |= 0x20;     // Bit5
}

void LCD_GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTM | GPIO_PORTK);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTM | GPIO_PORTK)) !=
           (GPIO_PORTM | GPIO_PORTK)) {
    };

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTM_AMSEL_R = 0x00;
    GPIO_PORTK_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTM_PCTL_R = 0x00;
    GPIO_PORTK_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTM_DIR_R |= 0x07; // Bit0-2
    GPIO_PORTK_DIR_R |= 0xFF; // Bit0-7

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTM_AFSEL_R = 0x00;
    GPIO_PORTK_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTM_DEN_R |= 0x07; // Bit0-2
    GPIO_PORTK_DEN_R |= 0xFF; // Bit0-7
}

void Motor_GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTH);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & GPIO_PORTH) != GPIO_PORTH) {
    }

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTH_AHB_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTH_AHB_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTH_AHB_DIR_R |= 0x0F; // Bit0-3

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTH_AHB_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTH_AHB_DEN_R |= 0x0F; // Bit0-3
}

void Pot_GPIO_Init(void) {
    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTE);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & GPIO_PORTE) != GPIO_PORTE) {
    }

    // 2. Setar o BIT4 do AMSEL para habilitar a analógica
    GPIO_PORTE_AHB_AMSEL_R = 0x10;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTE_AHB_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTE_AHB_DIR_R |= 0x00;

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTE_AHB_AFSEL_R = 0x00;

    // 6. Limpar os bits de DEN para habilitar I/O analogica
    GPIO_PORTE_AHB_DEN_R |= 0x00;
}

void PortN_Output(uint32_t valor) {
    uint32_t temp;
    // vamos zerar somente os bits menos significativos
    // para uma escrita amigável nos bits 0 e 1
    temp = GPIO_PORTN_DATA_R & 0xFC;
    // agora vamos fazer o OR com o valor recebido na função
    temp = temp | valor;
    GPIO_PORTN_DATA_R = temp;
}

void PortA_Output(uint32_t valor) {
    GPIO_PORTA_AHB_DATA_R =
        (GPIO_PORTA_AHB_DATA_R & (~GPIO_PORTA_AHB_DIR_R)) | valor;
}

void PortB_Output(uint32_t valor) {
    GPIO_PORTB_AHB_DATA_R =
        (GPIO_PORTB_AHB_DATA_R & (~GPIO_PORTB_AHB_DIR_R)) | valor;
}

void PortQ_Output(uint32_t valor) {
    GPIO_PORTQ_DATA_R = (GPIO_PORTQ_DATA_R & (~GPIO_PORTQ_DIR_R)) | valor;
}

void PortK_Output(uint32_t valor) {
    GPIO_PORTK_DATA_R = (GPIO_PORTK_DATA_R & (~GPIO_PORTK_DIR_R)) | valor;
}

void PortE_Output(uint32_t valor) {
    GPIO_PORTE_AHB_DATA_R =
        (GPIO_PORTE_AHB_DATA_R & (~GPIO_PORTE_AHB_DIR_R)) | valor;
}

void PortF_Output(uint32_t valor) {
    GPIO_PORTF_AHB_DATA_R =
        (GPIO_PORTF_AHB_DATA_R & (~GPIO_PORTF_AHB_DIR_R)) | valor;
}

void PortH_Output(uint32_t valor) {
    GPIO_PORTH_AHB_DATA_R =
        (GPIO_PORTH_AHB_DATA_R & (~GPIO_PORTH_AHB_DIR_R)) | valor;
}

void PortM_Output(uint32_t valor) {
    GPIO_PORTM_DATA_R = (GPIO_PORTM_DATA_R & (~GPIO_PORTM_DIR_R)) | valor;
}

void PortL_Output(uint32_t valor) {
    GPIO_PORTL_DATA_R = (GPIO_PORTL_DATA_R & (~GPIO_PORTL_DIR_R)) | valor;
}

void PortP_Output(uint32_t valor) {
    GPIO_PORTP_DATA_R = (GPIO_PORTP_DATA_R & (~GPIO_PORTP_DIR_R)) | valor;
}

uint32_t PortM_Input(void) {
    return GPIO_PORTM_DATA_R;
}

uint32_t PortJ_Input(void) {
    return GPIO_PORTJ_AHB_DATA_R;
}

uint32_t PortL_Input(void) {
    return GPIO_PORTL_DATA_R;
}

void PortM_ConfigDir(uint8_t saida) {
    GPIO_PORTM_DIR_R = (GPIO_PORTM_DIR_R & ~0xF0) | saida;
    PortM_Output(PortM_Input() & ~0xF0); // Limpa os da saida
}

void PortJ_Init(void) {
    GPIO_PORTJ_AHB_IM_R &= ~0x1;
    GPIO_PORTJ_AHB_IS_R &= ~0x1;
    GPIO_PORTJ_AHB_IBE_R &= ~0x1;
    GPIO_PORTJ_AHB_IEV_R &= ~0x1;
    GPIO_PORTJ_AHB_ICR_R |= 0x1;
    GPIO_PORTJ_AHB_IM_R |= 0x1;
    NVIC_EN1_R |= 0x080000;
    NVIC_PRI12_R |= 0xA0000000;
}
