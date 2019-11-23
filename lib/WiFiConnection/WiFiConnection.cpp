#include "Arduino.h"
#include "WiFi.h"
#include "WebServer.h"
#include "DNSServer.h"
#include "WiFiManager.h"
#include "WiFiConnection.h"

void WiFiConnection::wifiSetup()
{
    WiFiManager wifiManager;
 
    // Callback para cuando entra en modo de configuración AP (Access Point)
    wifiManager.setAPCallback(this->configModeCallback); 
    
    // Callback para cuando se conecta a una red, es decir, cuando pasa a trabajar en modo estación
    wifiManager.setSaveConfigCallback(this->saveConfigCallback); 
 
    // Crea una red de nombre ESP_AP con password 12345678
    // wifiManager.autoConnect("ESP_AP", "12345678"); 
    wifiManager.startConfigPortal("ESP32 Baliza", "baliza2019");
}

void WiFiConnection::configModeCallback(WiFiManager *myWiFiManager) 
{  
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP()); // Imprime la IP del AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); // Imprime el SSID creado de Red // Callback que indica que guardamos una nueva red para conectarse (modo estación)
}

void WiFiConnection::saveConfigCallback() 
{
  Serial.println("Configuraçión guardada");
  Serial.println(WiFi.softAPIP()); // Imprime la IP del AP
  Serial.println("");
}