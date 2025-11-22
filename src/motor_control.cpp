#include "motor_control.h"

void setMotorPins(int in1, int in2, bool dir, uint8_t pwmVal, int pwmChannel)
{
  if (dir)
  { // forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  { // backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  ledcWrite(pwmChannel, pwmVal); // pwmVal = 0..255 si resolution=8
}

void moveForward(uint8_t speed)
{
  Serial.println("Mover adelante");
  setMotorPins(M1_IN1, M1_IN2, true, speed, PWM_CH_MOTOR_A);
  setMotorPins(M2_IN1, M2_IN2, true, speed, PWM_CH_MOTOR_B);
}

void moveBackward(uint8_t speed)
{
  Serial.println("Mover atras");
  setMotorPins(M1_IN1, M1_IN2, false, speed, PWM_CH_MOTOR_A);
  setMotorPins(M2_IN1, M2_IN2, false, speed, PWM_CH_MOTOR_B);
}

// helper: mover ambos servos al mismo ángulo
void setSteeringAngle(int angle)
{
  angle = constrain(angle, 0, 180);
  setServoAngle(SERVO_LEFT_PIN, PWM_CH_SERVO_L, angle-10);
  setServoAngle(SERVO_RIGHT_PIN, PWM_CH_SERVO_R, angle-40);
}

void turnLeft(uint8_t /*speed*/)
{
  Serial.println("Girar izquierda (solo servos)");
  const int STEERING_DELTA = 45; // ajusta según necesidad
  int angle = constrain(90 - STEERING_DELTA, 0, 180);
  setSteeringAngle(angle);
}

void turnRight(uint8_t /*speed*/)
{
  Serial.println("Girar derecha (solo servos)");
  const int STEERING_DELTA = 60; // ajusta según necesidad
  int angle = constrain(90 + STEERING_DELTA, 0, 180);
  setSteeringAngle(angle);
}

void stopMotors()
{
  Serial.println("STOP");
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2, LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);
  ledcWrite(PWM_CH_MOTOR_A, 0);
  ledcWrite(PWM_CH_MOTOR_B, 0);
}

// Servo: convierte ángulo 0-180 a pulso (1000..2000 us) con resolución dada
void setServoAngle(int pin, int channel, int angle)
{
  angle = constrain(angle, 0, 180);
  const int minPulse = 1000;                          // us
  const int maxPulse = 2000;                          // us
  int pulse = map(angle, 0, 180, minPulse, maxPulse); // us

  // para resolución N y freq = 50Hz, el valor de duty es:
  // duty = pulse_us * (2^res - 1) / period_us
  const long period_us = 1000000L / SERVO_FREQ; // 20000
  const long maxDuty = (1UL << SERVO_RES) - 1;
  uint32_t duty = (uint32_t)((pulse * (double)maxDuty) / (double)period_us);

  ledcWrite(channel, duty);
}

// Horn: usa ledcWriteTone para frecuencia. duration en ms
void horn(uint16_t freq, uint16_t durationMs)
{
  Serial.println("HORN!");
  ledcWriteTone(PWM_CH_BUZZER, freq);
  delay(durationMs);
  ledcWriteTone(PWM_CH_BUZZER, 0); // detener
}