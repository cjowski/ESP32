#ifndef ESP_API_H
#define ESP_API_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Json/EspConnection/EspConnection.h"
  #include "Json/WifiConnection/WifiConnection.h"
  #include "Json/WifiCredentials/WifiCredentials.h"

  class EspApi
  {
    private:
    const char* JSON_CONTENT_TYPE = "application/json";
    std::function<WifiConnectionStatus(char*, char*)> ConnectToWifi;
    EspServerStorage *Storage;

    AsyncWebServer *Server;
    HardwareSerial *PrintSerial;
    void Setup();

    public:
    EspApi(
      int serverPort,
      EspServerStorage *storage,
      HardwareSerial *printSerial,
      std::function<WifiConnectionStatus(char*, char*)> connectToWifiCallback
    );

    friend class EspServer;
  };

#endif