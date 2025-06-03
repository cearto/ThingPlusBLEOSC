/**
 * @file writePin.ino
 * @brief Writes digital or analog output to a specified pin using OSC over BLE.
 * 
 * Send OSC messages like "/thing/write 9 1" to set pin 9 HIGH,
 * or "/thing/write 26 127" to analog write 127 to pin 26.
 * 
 * Responds with "/thing/wrote <val>".
 * 
 * @author Cesar Torres
 * @license MIT
 */

#include "config.h" // update BLE definitions 
#include <BLEHandler.h>
#include <OSCHandler.h>

void setup() {
  Serial.begin(115200);
  setupBLE();
}

void loop() {
  delay(100);
}

void routeOSC(OSCMessage &msg) {
  if (msg.match("/thing/write")) {
    int pin = getIntArg(msg, 0);
    int val = getIntArg(msg, 1);

    if (val == 0 || val == 1) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, val);
    } else {
      // analogWrite logic
    }

    sendSampleOSC("/thing/wrote", val);
  }
}
