#include <Arduino.h>
#include <Led.h>
#include <WiFiConnection.h>
#include <APIService.h>

Led redLed(5);
Led yellowLed(19);
Led greenLed(21);
Led orangeLed(16);

WiFiConnection wifiConnecion;
APIService apiService("https://api.travis-ci.com", "SJKuP9WgGz-KLCb5B5MDdw");

void setup()
{
  Serial.begin(9600);
  //Serial.println("test1");
  wifiConnecion.wifiSetup();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
      delay(500);
      greenLed.blink();
      //Serial.println("test2");
      apiService.connectToAPI();
      
  }else
  {
    //Serial.println("test3");
    delay(500);
    redLed.blink();
  }
}
