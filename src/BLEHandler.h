// BLEHandler.h
// This header defines BLE setup and OSC-over-BLE message handling for ThingPlus devices.
// Author: Cesar Torres
// License: MIT

#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H

#include "config.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "OSCHandler.h"
#include "MemoryStream.h"

// Global references to BLE objects for RX/TX handling
extern BLEServer *pServer;
extern BLECharacteristic *pTxCharacteristic;
extern BLECharacteristic *pRxCharacteristic;
extern bool deviceConnected;
extern bool oldDeviceConnected;

/**
 * @brief Initializes BLE service, characteristics, and advertising.
 *
 * Usage:
 * ```cpp
 * void setup() {
 *   setupBLE();
 * }
 * ```
 */
void setupBLE();

/**
 * @brief Callback for BLE connection events.
 */
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) override {
    deviceConnected = true;
  }
  void onDisconnect(BLEServer *pServer) override {
    deviceConnected = false;
  }
};

/**
 * @brief Callback for BLE RX characteristic writes.
 * Converts incoming data into an OSCMessage and calls routeOSC().
 *
 * Example expected message: "/thing/read A0"
 */
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) override {
    String receivedMessage = pCharacteristic->getValue().c_str();
    OSCMessage oscReceived(receivedMessage.c_str());
    routeOSC(oscReceived); // Delegate to main application routing logic
  }
};

#endif // BLE_HANDLER_H