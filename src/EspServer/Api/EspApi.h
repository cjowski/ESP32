#ifndef ESP_API_H
#define ESP_API_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspServer/Api/Request/Controller/ControllerApiRequest.h"
  #include "EspServer/Api/Request/Server/ServerApiRequest.h"
  #include "EspServer/Api/Response/Controller/ControllerApiResponse.h"
  #include "EspServer/Api/Response/Server/ServerApiResponse.h"
  #include "EspServer/Api/WebSocket/EspWebSocket.h"
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Json/BooleanJson.h"
  #include "Json/EmptyJson.h"
  #include "Json/IntegerJson.h"
  #include "Json/EspConnection/EspConnection.h"
  #include "Json/WifiConnection/WifiConnection.h"
  #include "Json/WifiCredentials/WifiCredentials.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"

  class EspApi
  {
    private:
    const char* JSON_CONTENT_TYPE = "application/json";

    AsyncWebServer *Server;
    EspWebSocket *WebSocket;
    EspServerStorage *Storage;
    std::function<ServerApiResponse*(ServerApiRequest*)> SendRequestToServer;
    std::function<ControllerApiResponse*(ControllerApiRequest*)> SendRequestToController;
    bool DebugMode = false;

    void SetupHeaders();
    void SetupWebHandlers();

    public:
    EspApi(
      AsyncWebServer *server,
      EspServerStorage *storage,
      std::function<ServerApiResponse*(ServerApiRequest*)> sendRequestToServer,
      std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController,
      bool debugMode
    );
    void Setup();
    void Loop();
  };

#endif