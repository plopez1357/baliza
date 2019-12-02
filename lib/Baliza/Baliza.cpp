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

Baliza::Baliza(){}

void Baliza::connectToCIServer(){
    apiService.connectToAPI();
}

void Baliza::setupWiFi(){
    wifiConnecion.wifiSetup();
}

// I9aFEbTHtAB7uCiJ0T-MTA
// lnyoitp6IOciC01Dcp0Lbg
// https://api.travis-ci.org
void Baliza::setupAPIConeccion(){
    apiService.setCredentials();
}

void Baliza::checkAPIStatus(){   
    String state = apiService.getState();

    if(state.equals("passed")){
        this->passedBuild();
    }else if(state.equals("failed") || state.equals("errored") || state.equals("canceled")){
        this->failedBuild();
    }else if(state.equals("created") || state.equals("started")){
        this->startedBuild();
    }else if(state.equals("4XX")){
        this->httpConnectionError();
    }else{
        this->turnOffLeds();
    }
}

void Baliza::startedBuild(){
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    greenLed.blink();
}

void Baliza::passedBuild(){
    yellowLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    greenLed.turnOn();
}

void Baliza::failedBuild(){
    greenLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOff();
    redLed.turnOn();
}

void Baliza::httpConnectionError(){
    greenLed.turnOff();
    redLed.turnOff();
    orangeLed.turnOff();
    yellowLed.turnOn();
}

void Baliza::wifiDisconnected(){
    greenLed.turnOff();
    redLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOn();
}

void Baliza::turnOffLeds(){
    greenLed.turnOff();
    redLed.turnOff();
    yellowLed.turnOff();
    orangeLed.turnOff();
}