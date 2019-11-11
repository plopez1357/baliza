#include <Arduino.h>
#include <Baliza.h>
#include <Led.h>
#include <WiFiConnection.h>
#include <APIService.h>
#include <string>

// Settings
WiFiConnection wifiConnecion;
APIService apiService;
Led redLed(5);
Led yellowLed(19);
Led greenLed(21);
Led orangeLed(16);

Baliza::Baliza()
{  
}

void Baliza::setupWiFi() 
{
    wifiConnecion.wifiSetup();
}

void Baliza::setupAPIConeccion()
{
    apiService.connectToAPI("https://api.travis-ci.com", "SJKuP9WgGz-KLCb5B5MDdw");
}

void Baliza::checkAPIStatus()
{
    if(apiService.getState() == "passed"){
        this->passedBuild();
    }else if(apiService.getState() == "failed"||apiService.getState() == "errored"||apiService.getState() == "canceled" ){
        this->failedBuild();
    }else if(apiService.getState() != "200"){
        this->httpConnectionError();
    }
}

void Baliza::passedBuild() 
{
    if(_previousState != "passed"){
        greenLed.blink();
        greenLed.blink();
        delay(2000);
    }
    greenLed.turnOn();
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    _previousState = "passed";
    
}

void Baliza::failedBuild()
{
    if(_previousState != "failed"){
        redLed.blink();
        redLed.blink();
        delay(2000);
    }
    redLed.turnOn();
    greenLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOff();
    _previousState = "failed";
}

void Baliza::httpConnectionError()
{
    greenLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    yellowLed.turnOn();
    _previousState = "httpError";
}

void Baliza::wifiDisconnected()
{
    greenLed.turnOff();
    redLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOn();
    _previousState = "wifiDisconnected";
}




