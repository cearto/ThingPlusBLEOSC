# ThingPlusBLEOSC

**ThingPlusBLEOSC** is an Arduino-compatible library that enables [SparkFun Thing Plus (ESP32)](https://www.sparkfun.com/products/15663) devices to send and receive [Open Sound Control (OSC)](https://opensoundcontrol.stanford.edu/)-styled messages via Bluetooth Low Energy (BLE). It is designed for creative coding, interactive installations, and sensor-actuator projects that benefit from wireless communication with minimal setup.

---

## Features

- BLE GATT server using custom UUIDs
- OSC message parsing and routing
- Simple API for sending/receiving values
- Lightweight in-memory serialization
- Built for the ESP32 Thing Plus board

---

## Library Structure

```
ThingPlusBLEOSC/
├── src/
│   ├── BLEHandler.cpp/h
│   ├── OSCHandler.cpp/h
│   └── MemoryStream.h
├── examples/
│   ├── ioPin/
│   ├── readPin/
│   └── writePin/
├── library.properties
├── LICENSE
└── README.md
```

---

## 🚀 Getting Started

### 1. Install the Library

You can install manually by cloning this repo into your `~/Documents/Arduino/libraries` folder, or install via the Arduino Library Manager.

### 2. Configure Your UUIDs

Each example includes a `config.h` file:

```cpp
#define DEVICE_NAME "Thing"
#define SERVICE_UUID           "00000000-0000-0000-0000-000000000000"
#define CHARACTERISTIC_UUID_RX "00000000-0000-0000-0000-000000000000"
#define CHARACTERISTIC_UUID_TX "00000000-0000-0000-0000-000000000000"
```

Generate your own UUIDs using [uuidgenerator.net](https://www.uuidgenerator.net/).

---

## Examples

- [`ioPin`](examples/ioPin/ioPin.ino): Combined read/write interface using OSC.
- [`readPin`](examples/readPin/readPin.ino): Reads digital or analog pins via OSC.
- [`writePin`](examples/writePin/writePin.ino): Sets pin values (digital or analog PWM) via OSC.

Checkout the python sister library `BLEOSC` that allows you to send and receive OSC-styled messaged via BLE (to ThingPlusBLEOSC devices). 

---

##  Dependencies

Make sure the following libraries are installed via the Library Manager:

- [`OSC`](https://github.com/CNMAT/OSC) by Adrian Freed
- `ESP32 BLE Arduino` by Neil Kolban (usually pre-installed)

---

## License

This project is licensed under the [MIT License](LICENSE).

© 2025 Cesar Torres
