#include <Arduino.h>
#include <APIService.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

HTTPClient http;

APIService::APIService()
{
}

void APIService::connectToAPI(String urlOfBuild, String authorizationToken)
{
  _urlOfBuild = urlOfBuild;
  _authorizationToken = authorizationToken;
}

void APIService::setHeader()
{
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  // 26882066 jorocha
  // 26853908 plopez1357
  http.begin(_urlOfBuild + "/repo/26853908/builds?limit=1");
  http.addHeader("Travis-API-Version","3");
  http.addHeader("User-Agent","API Explorer");
  http.addHeader("Authorization","token " + _authorizationToken);
}  

String APIService::getState()
{
  setHeader();
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0){
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK){
      // get the value of "state"
      String json = http.getString();
      StaticJsonBuffer <4000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(json);
      String status = root["builds"][0]["state"];  
      Serial.println(status);
      return status;
    }else{
      // connection error 4XX
      String stringHttpCode = String(httpCode).substring(0,1) + "XX";
      return stringHttpCode;
    } 
  }else{
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return http.errorToString(httpCode).c_str();
  }
  http.end();
}




      




