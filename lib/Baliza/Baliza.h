#ifndef Baliza_h
#define Baliza_h

#include <Arduino.h>

class Baliza
{
    public:
        Baliza();
        void setupWiFi();
        void setupAPIConeccion();
        void checkAPIStatus();
        void startedBuild();
        void passedBuild();
        void failedBuild();
        void httpConnectionError();
        void wifiDisconnected();

};

#endif