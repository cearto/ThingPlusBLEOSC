#include "config.h"
#include "driver/ledc.h" // if using the LED library to do analogWrite
#include <BLEHandler.h>
#include <OSCHandler.h>

const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8;

void setup() {
  Serial.begin(115200);
  ledcSetup(pwmChannel, pwmFreq, pwmResolution); // Setup PWM channel
  setupBLE();
}

void loop() {
  delay(100);
}

void routeOSC(OSCMessage &msg) {
  if (msg.match("/thing/read*")) {
    String pinLabel = getStringArg(msg, 1); // First argument after address
    int value;

    if (pinLabel.startsWith("A")) {
      int pin = pinLabel.substring(1).toInt();
      value = analogRead(pin);
    } else {
      int pin = pinLabel.toInt();
      value = digitalRead(pin);
    }

    sendSampleOSC("/thing/value", value);

  } else if (msg.match("/thing/write*")) {
    int pin = getIntArg(msg, 1);
    int val = getIntArg(msg, 2);

    pinMode(pin, OUTPUT);

    if (val == 0 || val == 1) {
      digitalWrite(pin, val);
    } else {
      ledcAttachPin(pin, pwmChannel);
      ledcWrite(pwmChannel, val);
    }

    sendSampleOSC("/thing/wrote", val);
  }
}
