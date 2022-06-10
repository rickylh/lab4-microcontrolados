#include "motorDC.h"
#include "conversorAD.h"
#include "lcd.h"

static uint8_t _count_pwm;
static uint8_t _velocidade = 0;
static enum SentidoRotacao _sentido_rotacao;
static uint8_t _motor_ligado = 0;
static uint8_t _velocidade;

void Timer2A_Handler() {
    TIMER2_ICR_R |= 0x1; // ACK da interrupção

    if (_motor_ligado || _velocidade == 0) {
        _motor_ligado = 0;
        TIMER2_TAILR_R = 80e3 * (100 - _velocidade) / 100 - 1;
        PortE_Output(0); // Motor desligado
    } else {
        _motor_ligado = 1;
        TIMER2_TAILR_R = 80e3 * _velocidade / 100 - 1;
        if (_sentido_rotacao == HORARIO) {
            PortE_Output(1); // motor ligado no sentido horario
        } else if (_sentido_rotacao == ANTI_HORARIO) {
            PortE_Output(2); // motor ligado no sentido anti-horario
        }
    }
}

void MotorDC_Init() {

    // 1a. Ativar o clock para a porta setando o bit correspondente no
    // registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= (GPIO_PORTE | GPIO_PORTF);
    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
    while ((SYSCTL_PRGPIO_R & (GPIO_PORTE | GPIO_PORTF)) !=
           (GPIO_PORTE | GPIO_PORTF)) {
    }

    // 2. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTE_AHB_AMSEL_R = 0x00;
    GPIO_PORTF_AHB_AMSEL_R = 0x00;

    // 3. Limpar PCTL para selecionar o GPIO
    GPIO_PORTE_AHB_PCTL_R = 0x00;
    GPIO_PORTF_AHB_PCTL_R = 0x00;

    // 4. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTE_AHB_DIR_R |= 0x0F; // Bit0-1
    GPIO_PORTF_AHB_DIR_R |= 0x0C; // Bit2

    // 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função
    // alternativa
    GPIO_PORTE_AHB_AFSEL_R = 0x00;
    GPIO_PORTF_AHB_AFSEL_R = 0x00;

    // 6. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTE_AHB_DEN_R |= 0x0F; // Bit0-1
    GPIO_PORTF_AHB_DEN_R |= 0x0C; // Bit2

    // inicializa o timer para o PWM
    initTimerPeriodicoS(10);
    PortF_Output(0xC);
}

// velocidade de 0 a 10
void MotorDC_setSentido(enum SentidoRotacao sentido_rotacao) {
    _sentido_rotacao = sentido_rotacao;
}

void MotorDC_setVelocidade(int velocidade) {
    _velocidade = velocidade;
}

void MotorDC_config(enum SentidoRotacao sentido_rotacao, int velocidade) {
    MotorDC_setSentido(sentido_rotacao);
    MotorDC_setVelocidade(velocidade);
}
