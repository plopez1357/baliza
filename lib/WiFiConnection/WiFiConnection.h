#ifndef WiFiConnection_h
#define WiFiConnection_h

#include "Arduino.h"
#include "WifiManager.h"

class WiFiConnection
{
    public:
        void wifiSetup();
        static void configModeCallback(WiFiManager *myWiFiManager);
        static void saveConfigCallback();
};

#endif