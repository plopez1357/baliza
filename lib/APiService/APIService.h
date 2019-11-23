#ifndef APIService_h
#define APIService_h

#include "Arduino.h"

class APIService
{
    public:
        APIService();
        void connectToAPI(String urlOfBuild, String authorizationToken);
        String getState();
    private:
        String _urlOfBuild;
        String _authorizationToken;
        void setHeader();   
};

#endif