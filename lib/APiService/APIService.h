#ifndef APIService_h
#define APIService_h

#include "Arduino.h"

class APIService
{
    public:
        APIService(String urlOfBuild, String authorizationToken);
        void connectToAPI();
        void getStatus();
    private:
        String _urlOfBuild;
        String _authorizationToken;
};

#endif