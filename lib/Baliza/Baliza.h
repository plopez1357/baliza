#ifndef Baliza_h
#define BAliza_h

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
        void turnOffLeds();
};

#endif