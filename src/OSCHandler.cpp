// OSCHandler.cpp
#include "OSCHandler.h"
#include "BLEHandler.h"  // Access BLE characteristic pointers

void sendSimpleOSC(const char* address) {
    sendOSC(address, nullptr, 0);
}

void sendSampleOSC(const char* address, int value) {
    sendOSC(address, &value, 1);
}

void sendOSC(const char *address, const int *args, int numArgs) {
    OSCMessage msg(address);
    for (int i = 0; i < numArgs; i++) {
        msg.add((int32_t)args[i]);
    }

    uint8_t oscMessage[256];
    MemoryStream memStream(oscMessage, sizeof(oscMessage));
    msg.send(memStream);
    int messageLength = memStream.length();

    pTxCharacteristic->setValue(oscMessage, messageLength);
    pTxCharacteristic->notify();

    Serial.print("Sent OSC to ");
    Serial.print(address);
    if (numArgs > 0) {
        Serial.print(" with args: ");
        for (int i = 0; i < numArgs; i++) {
            Serial.print(args[i]);
            Serial.print(" ");
        }
    }
    Serial.println();
}

String getStringArg(OSCMessage &msg, int index) {
    char buffer[64];
    msg.getAddress(buffer, 0, sizeof(buffer));

    char *token = strtok(buffer, " ");
    for (int i = 0; i < index && token != nullptr; i++) {
        token = strtok(nullptr, " ");
    }
    return (token != nullptr) ? String(token) : "";
}

int getIntArg(OSCMessage &msg, int index) {
    char buffer[64];
    msg.getAddress(buffer, 0, sizeof(buffer));

    char *token = strtok(buffer, " ");
    for (int i = 0; i < index && token != nullptr; i++) {
        token = strtok(nullptr, " ");
    }
    return (token != nullptr) ? atoi(token) : 0;
}

float getFloatArg(OSCMessage &msg, int index) {
    char buffer[64];
    msg.getAddress(buffer, 0, sizeof(buffer));

    char *token = strtok(buffer, " ");
    for (int i = 0; i < index && token != nullptr; i++) {
        token = strtok(nullptr, " ");
    }
    return (token != nullptr) ? atof(token) : 0.0;
}
