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
Led orangeLed(18);

Baliza::Baliza()
{  
}

void Baliza::setupWiFi() 
{
    wifiConnecion.wifiSetup();
}

void Baliza::setupAPIConeccion()
{
    apiService.connectToAPI("https://api.travis-ci.org", "lnyoitp6IOciC01Dcp0Lbg");
}

void Baliza::checkAPIStatus()
{   
    String state = apiService.getState();

    if(state.equals("passed")){
        this -> passedBuild();
    }else if(state.equals("failed") || state.equals("errored") || state.equals("canceled")){
        this -> failedBuild();
    }else if(state.equals("created") || state.equals("started")){
        this -> startedBuild();
    }else if(state.equals("4XX")){
        this -> httpConnectionError();
    }
}

void Baliza::startedBuild() 
{
    greenLed.blink();
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    
}

void Baliza::passedBuild() 
{
    greenLed.turnOn();
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    
}

void Baliza::failedBuild()
{
    redLed.turnOn();
    greenLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOff();
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




