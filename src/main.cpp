#include <Arduino.h>
#include <Led.h>
#include <WiFiConnection.h>
#include <APIService.h>

/*Led redLed(5);
Led yellowLed(19);
Led greenLed(21);*/
Led orangeLed(18); //fallo coneccion WIFI

WiFiConnection wifiConnecion;
APIService apiService;

void setup()
{
  Serial.begin(9600);
  wifiConnecion.wifiSetup();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
      delay(1000);
      apiService.connectToAPI("https://api.travis-ci.com", "SJKuP9WgGz-KLCb5B5MDdw");
      apiService.getState();
      apiService.activateLed();
      
  }else
  {
    delay(500);
    orangeLed.blink();
  }
}
