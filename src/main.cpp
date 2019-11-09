#include <Arduino.h>
#include <Led.h>
#include <WiFiConnection.h>

Led redLed(5);
Led yellowLed(19);
Led greenLed(21);
Led orangeLed(16);

WiFiConnection wifiConnecion;

void setup() {
  Serial.begin(115200);
  wifiConnecion.wifiSetup();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
      delay(500);
      greenLed.blink();
  }else{
      delay(500);
      redLed.blink();
  }
}
