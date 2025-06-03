/**
 * @file ioPin.ino
 * @brief Full OSC I/O Example for ESP32 ThingPlus using BLE
 * 
 * Supports both analog/digital read and write via OSC messages over BLE.
 * 
 * Accepted messages:
 *   - "/thing/read A0" or "/thing/read 9" → reads value from pin
 *   - "/thing/write 25 255" or "/thing/write 9 0" → writes value to pin
 * 
 * Responds with:
 *   - "/thing/value <val>" on read
 *   - "/thing/wrote <val>" on write
 * 
 * PWM writes automatically attach the pin to a LEDC channel.
 * 
 * @author Cesar Torres
 * @license MIT
 */

#include "config.h" // update BLE definitions 
#include <BLEHandler.h>
#include <OSCHandler.h>

const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8;

void setup() {
  Serial.begin(115200);
  ledcSetup(pwmChannel, pwmFreq, pwmResolution); // Setup PWM channel
  setupBLE(); // Initialize BLE OSC interface
}

void loop() {
  delay(100);
}

// Route incoming OSC messages to read/write handlers
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

  } else if (msg.match("/thing/write")) {
    int pin = msg.getInt(0);
    int val = msg.getInt(1);

    if (val == 0 || val == 1) {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, val);
    } else {
      ledcAttachPin(pin, pwmChannel);
      ledcWrite(pwmChannel, val);
    }

    sendSampleOSC("/thing/wrote", val);
  }
}
