#ifndef ESP_API_H
#define ESP_API_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspServer/Api/Request/ApiRequest.h"
  #include "EspServer/Api/Response/Controller/ControllerApiResponse.h"
  #include "EspServer/Api/Response/Server/ServerApiResponse.h"
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Json/EmptyJson.h"
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
    std::function<ServerApiResponse*(ApiRequest*)> SendRequestToServer;
    std::function<ControllerApiResponse*(ApiRequest*)> SendRequestToController;

    void Setup();

    public:
    EspApi(
      int serverPort,
      EspServerStorage *storage,
      HardwareSerial *printSerial,
      std::function<ServerApiResponse*(ApiRequest*)> sendRequestToServer,
      std::function<ControllerApiResponse*(ApiRequest*)> sendRequestToController
    );
    
    friend class EspServer;
  };

#endif