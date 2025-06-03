// BLEHandler.cpp
#include "BLEHandler.h"
#include "OSCHandler.h"

BLEServer *pServer = nullptr;
BLECharacteristic *pTxCharacteristic = nullptr;
BLECharacteristic *pRxCharacteristic = nullptr;
bool deviceConnected = false;
bool oldDeviceConnected = false;

void setupBLE() {
    Serial.print("Initializing BLE device: ");
    Serial.println(DEVICE_NAME);

    BLEDevice::init(DEVICE_NAME);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    // TX: Notifies clients
    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
    pTxCharacteristic->addDescriptor(new BLE2902());

    // RX: Accepts write from clients
    pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyCallbacks());

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    BLEAdvertisementData advertisementData;
    advertisementData.setName(DEVICE_NAME);
    pAdvertising->setScanResponseData(advertisementData);

    pAdvertising->stop();
    delay(500);
    pAdvertising->start();

    Serial.println("BLE advertising started. Awaiting client connection...");
}