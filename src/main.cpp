#include "config.h"
#include "ble_callbacks.h"

// Definir variables globales
BLECharacteristic *pCharacteristic;
bool deviceConnected;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Iniciando BLE RC Car...");

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

  // Empezar advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("BLE listo, esperando conexión...");
}

void loop()
{
  // No necesitas nada aquí aún
}