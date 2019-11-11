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
        void successfulBuild();
        void failedBuild();
        void httpConnectionError();
        void wifiDisconnected();
};

#endif