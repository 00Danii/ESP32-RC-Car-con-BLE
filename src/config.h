#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// ====== UUIDs BLE ======
#define SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"

// ====== Pines ======
const int SERVO_LEFT_PIN = 13;  // D13
const int SERVO_RIGHT_PIN = 12; // D12
const int M1_IN1 = 27;          // Motor1 IN1
const int M1_IN2 = 26;          // Motor1 IN2
const int M2_IN1 = 25;          // Motor2 IN3
const int M2_IN2 = 33;          // Motor2 IN4
const int ENA_PIN = 14;         // PWM motor1
const int ENB_PIN = 32;         // PWM motor2
const int RELAY_REAR_PIN = 15;  // relé motor trasero
const int LIGHTS_PIN = 2;       // luces delanteras
const int BUZZER_PIN = 4;       // buzzer/claxon

// Indica si el relé se activa con nivel LOW (true) o HIGH (false)
const bool RELAY_ACTIVE_LOW = true;

// Indica si las luces se activan con nivel LOW (true) o HIGH (false)
const bool LIGHTS_ACTIVE_LOW = false;

// ====== LEDC / PWM config ======
const int PWM_FREQ_MOTORS = 20000; // 20 kHz para motores
const int PWM_RES_MOTORS = 8;      // 8 bits (0-255)
const int PWM_CH_MOTOR_A = 0;      // canal ledc
const int PWM_CH_MOTOR_B = 1;
const int SERVO_FREQ = 50; // 50 Hz para servos
const int SERVO_RES = 16;  // 16 bits para mejor resolución
const int PWM_CH_SERVO_L = 2;
const int PWM_CH_SERVO_R = 3;
const int PWM_CH_BUZZER = 4;

// ====== Variables globales ======
extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;
extern bool relayRearState;
extern bool lightsState;

// ====== Prototipos ======
void moveForward(uint8_t speed);
void moveBackward(uint8_t speed);
void turnLeft(uint8_t speed);
void turnRight(uint8_t speed);
void stopMotors();
void setServoAngle(int pin, int channel, int angle);
void horn(uint16_t freq, uint16_t durationMs);

#endif