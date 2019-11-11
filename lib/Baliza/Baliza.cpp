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
        this->successfulBuild();
    }else if(apiService.getState() == "failed"){
        this->failedBuild();
    }else if(apiService.getState() != "200"){
        this->httpConnectionError();
    }
}

void Baliza::successfulBuild() 
{
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    greenLed.turnOn();
}

void Baliza::failedBuild()
{
    greenLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOff();
    redLed.turnOn();
}

void Baliza::httpConnectionError()
{
    greenLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    yellowLed.turnOn();
}

void Baliza::wifiDisconnected()
{
    greenLed.turnOff();
    redLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOn();
}




