#ifndef APIService_h
#define APIService_h

#include "Arduino.h"

class APIService
{
    public:
        APIService();
        void connectToAPI(String urlOfBuild, String authorizationToken);
        String getState();
};

#endif