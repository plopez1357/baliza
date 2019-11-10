#include "Arduino.h"
#include "Led.h"
#include "APIService.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

HTTPClient http;
Led redLed(5);
Led yellowLed(19);
Led greenLed(21);

APIService::APIService()
{
}

void APIService::connectToAPI(String urlOfBuild, String authorizationToken)
{
  Serial.print("[HTTP] begin...\n");

  // configure traged server and url
  http.begin(urlOfBuild + "/builds?limit=1");
  http.addHeader("Travis-API-Version","3");
  http.addHeader("User-Agent","API Explorer");
  http.addHeader("Authorization","token " + authorizationToken);
}        

String APIService::getState()
{
  //String state;
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server

    if(httpCode == HTTP_CODE_OK )
    {
      String json = http.getString();
      StaticJsonBuffer <3000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(json);
      String status = root["builds"][0]["state"];  
      _state = status;
      Serial.println(status);
      return _state;
      Serial.println(_state);
      
    }else
    {
      return "Code:" + httpCode;
    } 
  }else 
  {
    return http.errorToString(httpCode).c_str();
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  //http.end();
}

void APIService::activateLed()
{
  if(_state == "passed")
  {
    greenLed.turnOn();
    redLed.turnOff();
    yellowLed.turnOff();

  }else if(_state == "failed")
  {
    greenLed.turnOff();
    redLed.turnOn();
    yellowLed.turnOff();
      
  }/*else if(_state == "errored")
  {
      
      
  }else if(_state == "started")0
  {
      
      
  }else if(_state == "canceled")
  {
    
  }*/
}


      




