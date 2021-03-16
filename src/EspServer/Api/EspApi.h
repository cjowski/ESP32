#ifndef ESP_API_H
#define ESP_API_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspApiRequest.h"
  #include "EspApiResponse.h"
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Json/EspConnection/EspConnection.h"
  #include "Json/WifiConnection/WifiConnection.h"
  #include "Json/WifiCredentials/WifiCredentials.h"

  class EspApi
  {
    private:
    const char* JSON_CONTENT_TYPE = "application/json";
    EspServerStorage *Storage;
    AsyncWebServer *Server;
    HardwareSerial *PrintSerial;
    std::function<EspApiResponse(EspApiRequest)> SendRequestToServer;

    void Setup();

    public:
    EspApi(
      int serverPort,
      EspServerStorage *storage,
      HardwareSerial *printSerial,
      std::function<EspApiResponse(EspApiRequest)> sendRequestToServer
    );
    
    friend class EspServer;
  };

#endif