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

void setup()
{
  Serial.begin(9600);
  baliza.setupWiFi();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  //if (wifiMulti.run() == WL_CONNECTED)
  {
    delay(1000);
    baliza.setupAPIConeccion();
    baliza.checkAPIStatus();
  }else
  {
    delay(500);
    Serial.println("NO SE PUDO CONECTAR A WIFI");
    baliza.wifiDisconnected();
  }
}
