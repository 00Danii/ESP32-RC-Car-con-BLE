#include "ble_callbacks.h"

void MyServerCallbacks::onConnect(BLEServer *pServer)
{
  deviceConnected = true;
  Serial.println("Dispositivo conectado");
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer)
{
  deviceConnected = false;
  Serial.println("Dispositivo desconectado");
  // volver a publicar advertising
  BLEDevice::startAdvertising();
}

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string rx = pCharacteristic->getValue();
  if (rx.length() == 0)
    return;
  char cmd = rx[0];
  Serial.printf("Comando: %c\n", cmd);

  uint8_t speed = 200; // valor PWM 0-255 por defecto

  switch (cmd)
  {
  case 'F':
    moveForward(speed);
    break;
  case 'B':
    moveBackward(speed);
    break;
  case 'L':
    turnLeft(speed);
    break;
  case 'R':
    turnRight(speed);
    break;
  case 'S':
    stopMotors();
    break;
  case 'H':
    horn(1000, 300);
    break;  // claxon 1kHz 300ms
  case '1': // toggle relé trasero
    relayRearState = !relayRearState;
    digitalWrite(RELAY_REAR_PIN, relayRearState ? HIGH : LOW);
    break;
  case '2': // toggle luces
    lightsState = !lightsState;
    digitalWrite(LIGHTS_PIN, lightsState ? HIGH : LOW);
    break;
  default:
    Serial.println("Comando desconocido");
    break;
  }
}