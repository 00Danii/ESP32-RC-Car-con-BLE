#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "config.h"

// Funciones de control
void setMotorPins(int in1, int in2, bool dir, uint8_t pwmVal, int pwmChannel);
void moveForward(uint8_t speed);
void moveBackward(uint8_t speed);
void turnLeft(uint8_t speed);
void turnRight(uint8_t speed);
void stopMotors();
void setServoAngle(int pin, int channel, int angle);
void horn(uint16_t freq, uint16_t durationMs);

#endif