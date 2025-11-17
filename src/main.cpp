#include "config.h"
#include "ble_callbacks.h"
#include "motor_control.h"

// Definir variables globales
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool relayRearState = false;
bool lightsState = false;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 RC - BLE inicializando...");

  // Pines digitales
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  pinMode(RELAY_REAR_PIN, OUTPUT);
  pinMode(LIGHTS_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_REAR_PIN, LOW);
  digitalWrite(LIGHTS_PIN, LOW);

  // Configurar ledc para motores
  ledcSetup(PWM_CH_MOTOR_A, PWM_FREQ_MOTORS, PWM_RES_MOTORS);
  ledcAttachPin(ENA_PIN, PWM_CH_MOTOR_A);

  ledcSetup(PWM_CH_MOTOR_B, PWM_FREQ_MOTORS, PWM_RES_MOTORS);
  ledcAttachPin(ENB_PIN, PWM_CH_MOTOR_B);

  // Servos: 50Hz - 16-bit resolution
  ledcSetup(PWM_CH_SERVO_L, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(SERVO_LEFT_PIN, PWM_CH_SERVO_L);

  ledcSetup(PWM_CH_SERVO_R, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(SERVO_RIGHT_PIN, PWM_CH_SERVO_R);

  // Buzzer: usaremos ledcWriteTone
  ledcAttachPin(BUZZER_PIN, PWM_CH_BUZZER);

  // Valores iniciales
  stopMotors();
  setServoAngle(SERVO_LEFT_PIN, PWM_CH_SERVO_L, 90);  // centro
  setServoAngle(SERVO_RIGHT_PIN, PWM_CH_SERVO_R, 90); // centro

  // ===== BLE =====
  BLEDevice::init("ESP32-RC-CAR");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_WRITE_NR);
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("BLE listo, esperando conexión...");
}

void loop()
{
  // nada aquí por ahora
  delay(100);
}