#include <Arduino.h>
#include <Led.h>
#include <WiFiConnection.h>
#include <APIService.h>
#include <Baliza.h>

/*
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;*/

Baliza baliza;

void setup() {
  Serial.begin(115200);
  baliza.setupWiFi();
  baliza.connectToCIServer();
}

void loop() {
  // if (wifiMulti.run() == WL_CONNECTED)
  if (WiFi.status() == WL_CONNECTED){
    delay(1000);
    baliza.setupAPIConeccion();
    baliza.checkAPIStatus();
  }else{
    delay(1000);
    Serial.println("NO SE PUDO CONECTAR A WIFI");
    baliza.wifiDisconnected();
  }
}
