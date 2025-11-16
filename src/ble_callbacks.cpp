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
}

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string rxValue = pCharacteristic->getValue();

  if (rxValue.length() > 0)
  {
    char cmd = rxValue[0];
    Serial.printf("Comando recibido: %c\n", cmd);

    switch (cmd)
    {
    case 'F':
      Serial.println("➡ AVANZAR");
      break;
    case 'B':
      Serial.println("⬅ RETROCEDER");
      break;
    case 'L':
      Serial.println("⬅ IZQUIERDA");
      break;
    case 'R':
      Serial.println("➡ DERECHA");
      break;
    case 'S':
      Serial.println("⏹ STOP");
      break;
    default:
      Serial.println("? Comando desconocido");
      break;
    }
  }
}