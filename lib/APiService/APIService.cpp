#include "Arduino.h"
#include "Led.h"
#include "APIService.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

HTTPClient http;

APIService::APIService(String urlOfBuild, String authorizationToken)
{
  _urlOfBuild = urlOfBuild;
  _authorizationToken = authorizationToken;
}

void APIService::getStatus()
{

}

void APIService::connectToAPI()
{
  Serial.print("[HTTP] begin...\n");

  // configure traged server and url
  http.begin(_urlOfBuild + "/builds?limit=1");
  http.addHeader("Travis-API-Version","3");
  http.addHeader("User-Agent","API Explorer");
  http.addHeader("Authorization","token" + _authorizationToken);
        
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
      String state = root["builds"][0]["state"];
              
      if(state == "passed")
      {
        Serial.println(state);

      }else if(state == "failed")
      {
        Serial.println(state);
                  
      }else if(state == "errored")
      {
        Serial.println(state);
                
      }else if(state == "started")
      {
        Serial.println(state);
                
      }else if(state == "canceled")
      {
          Serial.println(state);
      }      
    } 

  } else 
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
}        
      




