#include "Arduino.h"
#include "Led.h"
#include "APIService.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>

HTTPClient http;

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
      return status;
      Serial.println(status);
      
    }else
    {
      return "Code:" + httpCode;
    } 
  }else 
  {
    return http.errorToString(httpCode).c_str();
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}




      




