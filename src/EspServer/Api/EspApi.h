#ifndef ESP_API_H
#define ESP_API_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspServer/Api/Request/Controller/ControllerApiRequest.h"
  #include "EspServer/Api/Request/Server/ServerApiRequest.h"
  #include "EspServer/Api/Response/Controller/ControllerApiResponse.h"
  #include "EspServer/Api/Response/Server/ServerApiResponse.h"
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
    AsyncWebSocket *WebSocket;
    AsyncWebSocketClient *WebSocketClient = NULL;
    EspServerStorage *Storage;
    HardwareSerial *PrintSerial;
    std::function<ServerApiResponse*(ServerApiRequest*)> SendRequestToServer;
    std::function<ControllerApiResponse*(ControllerApiRequest*)> SendRequestToController;

    uint32_t WebSocketUpdateDelay = 40;
    uint32_t PreviousWebSocketUpdate = 0;

    void Setup();
    void OnWebSocketEvent(
      AsyncWebSocket *server,
      AsyncWebSocketClient *client,
      AwsEventType type,
      void *arg,
      uint8_t *data,
      size_t len
    );
    void Loop();

    public:
    EspApi(
      int serverPort,
      EspServerStorage *storage,
      HardwareSerial *printSerial,
      std::function<ServerApiResponse*(ServerApiRequest*)> sendRequestToServer,
      std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController
    );
    
    friend class EspServer;
  };

#endif