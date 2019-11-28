#include <Arduino.h>
#include <APIService.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include <SPIFFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

HTTPClient http;
AsyncWebServer server1(81);

APIService::APIService(){}

void APIService::connectToAPI() {
  this->startSPIFFS();
  Serial.println("Ingresar a esta IP para colocar las credenciales");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  delay(5000);
  server1.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", INDEX_HTML);
  });
  
  server1.on("/get", HTTP_GET, [this] (AsyncWebServerRequest *request) {
    String inputUrl = request->arg("inputUrl").c_str();
    String inputToken = request->arg("inputToken").c_str();
    writeFile(SPIFFS, "/inputUrl.txt", inputUrl.c_str());
    writeFile(SPIFFS, "/inputToken.txt", inputToken.c_str());
    request->send(200, "text/html", SAVE_HTML);
  });
  server1.begin();
}

void APIService::writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

void APIService::startSPIFFS() {
  if(!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }else{
    SPIFFS.remove("/inputUrl.txt");
    SPIFFS.remove("/inputToken.txt");
  }
}

String APIService::readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()) {
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()) {
    fileContent+=String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
}

void APIService::setCredentials() {
  // _urlOfBuild = urlOfBuild;
  // _authorizationToken = authorizationToken;
  _urlOfBuild = readFile(SPIFFS, "/inputUrl.txt");
  _authorizationToken = readFile(SPIFFS, "/inputToken.txt");
}

void APIService::setHeader() {
  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  // 26882066 jorocha
  // 26853908 plopez1357
  http.begin(_urlOfBuild + "/repo/26853908/builds?limit=1");
  http.addHeader("Travis-API-Version","3");
  http.addHeader("User-Agent","API Explorer");
  http.addHeader("Authorization","token " + _authorizationToken);
}  

String APIService::getState() {
  setHeader();
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      // get the value of "state"
      String json = http.getString();
      StaticJsonBuffer <4000> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(json);
      String status = root["builds"][0]["state"];  
      Serial.println(status);
      return status;
    } else {
      // connection error 4XX
      String stringHttpCode = String(httpCode).substring(0,1) + "XX";
      return stringHttpCode;
    } 
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return http.errorToString(httpCode).c_str();
  }
  http.end();
}




      




