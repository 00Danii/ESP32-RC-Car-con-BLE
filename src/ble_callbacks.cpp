#include "ble_callbacks.h"
#include "motor_control.h"
#include <cctype>

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

  uint8_t speed = 200;           // valor PWM 0-255 por defecto
  const int STEERING_DELTA = 30; // ajuste para FR/FL/BR/BL

  // Comandos compuestos:
  // "FR" (forward + right), "FL" (forward + left)
  // "BR" (backward + right), "BL" (backward + left)
  if ((rx == "FR") || (rx == "fr"))
  {
    int angle = constrain(90 + STEERING_DELTA, 0, 180);
    setSteeringAngle(angle);
    moveForward(speed);
    Serial.println("Comando: FR -> girar derecha y avanzar");
    return;
  }
  if ((rx == "FL") || (rx == "fl"))
  {
    int angle = constrain(90 - STEERING_DELTA, 0, 180);
    setSteeringAngle(angle);
    moveForward(speed);
    Serial.println("Comando: FL -> girar izquierda y avanzar");
    return;
  }
  if ((rx == "BR") || (rx == "br"))
  {
    int angle = constrain(90 + STEERING_DELTA, 0, 180);
    setSteeringAngle(angle);
    moveBackward(speed);
    Serial.println("Comando: BR -> girar derecha y retroceder");
    return;
  }
  if ((rx == "BL") || (rx == "bl"))
  {
    int angle = constrain(90 - STEERING_DELTA, 0, 180);
    setSteeringAngle(angle);
    moveBackward(speed);
    Serial.println("Comando: BL -> girar izquierda y retroceder");
    return;
  }

  // Comando simple (un carácter)
  char cmd = toupper((unsigned char)rx[0]);
  Serial.printf("Comando: %c\n", cmd);

  switch (cmd)
  {
  case 'F':
    // volver servos a posición central antes de avanzar
    setSteeringAngle(90);
    moveForward(speed);
    break;
  case 'B':
    // volver servos a posición central antes de retroceder
    setSteeringAngle(90);
    moveBackward(speed);
    break;
  case 'L':
    turnLeft(speed); // ahora solo mueve servos
    break;
  case 'R':
    turnRight(speed); // ahora solo mueve servos
    break;
  case 'S':
    stopMotors();
    break;
  case 'H':
    horn(1000, 300);
    break;  // claxon 1kHz 300ms
  case '1': // toggle relé trasero
    relayRearState = !relayRearState;
    // Escribir nivel según si el relé es active LOW o active HIGH
    digitalWrite(RELAY_REAR_PIN,
                 relayRearState ? (RELAY_ACTIVE_LOW ? LOW : HIGH)
                                : (RELAY_ACTIVE_LOW ? HIGH : LOW));
    break;
  case '2': // toggle luces
    lightsState = !lightsState;
    digitalWrite(LIGHTS_PIN,
                 lightsState ? (LIGHTS_ACTIVE_LOW ? LOW : HIGH)
                             : (LIGHTS_ACTIVE_LOW ? HIGH : LOW));
    break;
  default:
    Serial.println("Comando desconocido");
    break;
  }
}