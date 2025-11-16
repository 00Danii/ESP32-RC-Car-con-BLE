#ifndef BLE_CALLBACKS_H
#define BLE_CALLBACKS_H

#include "config.h"

// Manejo de conexión BLE
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer) override;
  void onDisconnect(BLEServer *pServer) override;
};

// Manejo de escritura de comandos
class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic) override;
};

#endif