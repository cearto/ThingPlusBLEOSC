/**
 * @file readPin.ino
 * @brief Reads digital or analog input from a specified pin using OSC over BLE.
 * 
 * Send OSC messages like "/thing/read A0" or "/thing/read 9" to query pin values.
 * The device will respond with "/thing/value <val>".
 * 
 * @author Cesar Torres
 * @license MIT
 */

#include "config.h" // update BLE definitions 
#include <Arduino.h>  // ensures ledc* functions are visible
#include <BLEHandler.h>
#include <OSCHandler.h>

void setup() {
  Serial.begin(115200);
  setupBLE(); // Initialize BLE services
}

void loop() {
  delay(100);
}

void routeOSC(OSCMessage &msg) {
  if (msg.match("/thing/read")) {
    String pinLabel = msg.getString(0);
    int value;

    if (pinLabel.startsWith("A")) {
      int pin = pinLabel.substring(1).toInt();
      value = analogRead(pin);
    } else {
      int pin = pinLabel.toInt();
      value = digitalRead(pin);
    }

    sendSampleOSC("/thing/value", value);
  }
}
