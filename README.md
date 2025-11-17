# ESP32 RC Car con BLE

Este proyecto implementa un coche RC (Radio Control) controlado vía Bluetooth Low Energy (BLE) usando un ESP32. Incluye control de motores, servos para dirección, luces, relé trasero y buzzer para claxon.

## Requisitos

### Hardware
- ESP32 (modelo ESP32-DevKitC o similar).
- Motores DC con driver (ej. L298N).
- Servos para dirección (2 unidades).
- Relé para motor trasero.
- LEDs para luces.
- Buzzer para claxon.
- Batería (ej. 7.4V LiPo) y regulador de voltaje si es necesario.

### Software
- PlatformIO (instalado en VS Code).
- Librerías Arduino: BLEDevice, BLEUtils, BLEServer (incluidas en el framework ESP32 de PlatformIO).

## Instalación

1. Clona o descarga el proyecto en tu carpeta de PlatformIO: `c:\Users\<tu_usuario>\Documents\PlatformIO\Projects\rc-car`.
2. Abre el proyecto en VS Code con PlatformIO.
3. Verifica que el archivo `platformio.ini` esté configurado correctamente (debería incluir `framework = arduino` y `board = esp32dev`).

## Compilación y Subida

1. Conecta el ESP32 a tu PC vía USB.
2. En VS Code, abre el terminal integrado.
3. Ejecuta `pio run` para compilar.
4. Ejecuta `pio run -t upload` para subir el firmware al ESP32.
5. Abre el monitor serial con `pio device monitor` para ver logs.

## Uso

### Conexión BLE
- Una vez subido, el ESP32 inicia BLE con nombre "ESP32-RC-CAR".
- Usa una app BLE como "BLE Scanner" o "nRF Connect" en tu teléfono para conectarte.
- Escribe comandos en la característica `6e400002-b5a3-f393-e0a9-e50e24dcca9e` (tipo WRITE).

### Comandos Disponibles
Envía un carácter único a la característica BLE:

- `F`: Avanzar.
- `B`: Retroceder.
- `L`: Girar izquierda.
- `R`: Girar derecha.
- `S`: Detener motores.
- `H`: Claxon (1kHz, 300ms).
- `1`: Toggle relé trasero.
- `2`: Toggle luces.

### Configuración de Pines
Los pines están definidos en `src/config.h`. Ajusta según tu hardware si es necesario.

## Estructura del Proyecto
- `src/main.cpp`: Función principal (setup y loop).
- `src/config.h`: Constantes y prototipos.
- `src/ble_callbacks.h/.cpp`: Callbacks BLE.
- `src/motor_control.h/.cpp`: Funciones de control de motores y servos.
- `platformio.ini`: Configuración de PlatformIO.

