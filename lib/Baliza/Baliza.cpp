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
{   //Llamo una sola vez al .getState para que no tenga problemas con la autenticación
    String state = apiService.getState();

    if(state.equals("passed")){
        this->passedBuild();
    }else if(state.equals("failed") || state.equals("errored") || state.equals("canceled") 
            || state.equals("created") || state.equals("started") ){
        this->failedBuild();
    }else if(state != "200"){
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




