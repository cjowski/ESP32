#ifndef ESP_WEB_SOCKET_H
#define ESP_WEB_SOCKET_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include "EspServer/Storage/EspServerStorage.h"

  class EspWebSocket
  {
    private:
    const char* WEB_SOCKET_URL = "/esp32ws";
    const uint32_t WEB_SOCKET_UPDATE_DELAY = 40;
    uint32_t PreviousWebSocketUpdate = 0;

    AsyncWebServer *Server;
    AsyncWebSocket *WebSocket;
    AsyncWebSocketClient *WebSocketClient = NULL;
    EspServerStorage *Storage;
    bool DebugMode = false;

    public:
    EspWebSocket(
      AsyncWebServer *server,
      EspServerStorage *storage,
      bool debugMode
    );
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
  };

#endif