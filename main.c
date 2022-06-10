// main.c
// Desenvolvido para a placa EK-TM4C1294XL

#include "conversorAD.h"
#include "gpio.h"
#include "lcd.h"
#include "motorDC.h"
#include "timer.h"
#include "uart.h"
#include "utils.h"

// Funções escritas em assembly
void PLL_Init(void);
uint8_t verificarTeclado(void);

enum SentidoRotacao _sentido_rotacao = HORARIO;
uint8_t _velocidade = 0;

enum InputSource { INPUT_TERMINAL, INPUT_POTENCIOMETRO, INPUT_NONE };
enum InputSource _input_source = INPUT_NONE;

int32_t abs(int32_t n) {
    return n < 0 ? -n : n;
}

void printInfoMotor() {
    uartPrint("Velocidade = ");
    char str[32];
    itoa(_velocidade, str, 10);
    uartPrint(str);

    if (_sentido_rotacao == HORARIO) {
        uartPrintln(" e sentido de rotação Horário");
    } else {
        uartPrintln(" e sentido de rotaçao Anti-Horário");
    }
}

void getControle() {
    uartPrintln("Selecione o tipo de controle para o motor:\r\n"
                "p: potenciometro   t: terminal");
    enum InputSource new_input_source = INPUT_NONE;
    while (new_input_source == INPUT_NONE) {
        // Espera receber a informação do usuario
        while (!uartHasData())
            ;

        int value = uartRead();
        if (value == 'p' || value == 'P') {
            new_input_source = INPUT_POTENCIOMETRO;
            uartPrintln("Potenciômetro selecionado");
        } else if (value == 't' || value == 'T') {
            new_input_source = INPUT_TERMINAL;
            uartPrintln("Terminal selecionado");
        }
    }
    _input_source = new_input_source;
}

void getSentidoRotacao() {
    uartPrintln("Selecione o sentido de rotação:\r\n"
                "h: horário   a: anti-horário");
    enum SentidoRotacao _sentido_rotacao = NONE;
    while (_sentido_rotacao == NONE) {
        // Espera receber a informação do usuario
        while (!uartHasData())
            ;

        int value = uartRead();
        if (value == 'h' || value == 'H') {
            _sentido_rotacao = HORARIO;
            uartPrintln("Sentido de rotação: Horário");
            MotorDC_setSentido(_sentido_rotacao);
        } else if (value == 'a' || value == 'A') {
            _sentido_rotacao = ANTI_HORARIO;
            uartPrintln("Sentido de rotação: Anti-Horário");
            MotorDC_setSentido(_sentido_rotacao);
        }
    }
}

void updateFromPot() {
    static int old_vel = 0;
    int value = readPot();
    char str[32];
    itoa(value, str, 10);
    LCD_print_reset("Valor lido:", str);
    _velocidade = value * 100 / 4095;
    if (abs(old_vel - _velocidade) > 1) {
        MotorDC_setVelocidade(_velocidade);
        printInfoMotor();
        old_vel = _velocidade;
    }
}

void updateFromTerminal(char value) {
    if (value >= '0' && value <= '6') {
        _velocidade = value == '0' ? 0 : 40 + (value - '0') * 10;
        MotorDC_setVelocidade(_velocidade);
        printInfoMotor();
    }
}

int main(void) {
    PLL_Init();
    SysTick_Init();
    Pot_GPIO_Init();
    LCD_init();
    initConversorAD();
    uartInit();
    MotorDC_Init();

    uartPrintln("Motor Parado");
    getSentidoRotacao();
    getControle();

    char value;
    while (1) {
        if (uartHasData()) {
            value = uartRead();
            if (value == 'h' || value == 'H') {
                _sentido_rotacao = HORARIO;
                uartPrintln("Sentido de rotação: Horário");
                MotorDC_setSentido(_sentido_rotacao);
            } else if (value == 'a' || value == 'A') {
                _sentido_rotacao = ANTI_HORARIO;
                uartPrintln("Sentido de rotação: Anti-Horário");
                MotorDC_setSentido(_sentido_rotacao);
            } else if (value == 'p' | value == 'P') {
                _input_source = INPUT_POTENCIOMETRO;
            } else if (value == 't' || value == 'T') {
                _input_source = INPUT_TERMINAL;
            } else if (_input_source == INPUT_TERMINAL) {
                updateFromTerminal(value);
            }
            char str[32] = {value, 0};
            LCD_print_reset("Valor lido: ", str);
        }
        if (_input_source == INPUT_POTENCIOMETRO) {
            updateFromPot();
        }
    }
}
