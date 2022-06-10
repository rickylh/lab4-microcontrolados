#ifndef __MOTOR_DC__
#define __MOTOR_DC__

#include "gpio.h"
#include "stdint.h"
#include "timer.h"
#include "utils.h"

enum SentidoRotacao { HORARIO, ANTI_HORARIO, NONE };

void Timer2A_Handler();
void MotorDC_Init();
void MotorDC_setSentido(enum SentidoRotacao sentido_rotacao);
void MotorDC_setVelocidade(int velocidade);
void MotorDC_config(enum SentidoRotacao sentido_rotacao, int velocidade);
void atualizarMotor();

#endif // __MOTOR_DC__
