#include "EspWebSocket.h"

EspWebSocket::EspWebSocket(
  AsyncWebServer *server,
  EspServerStorage *storage,
  HardwareSerial *printSerial
)
{
  Server = server;
  WebSocket = new AsyncWebSocket(WEB_SOCKET_URL);
  Storage = storage;
  PrintSerial = printSerial;
}

void EspWebSocket::Setup()
{
  WebSocket->onEvent(
    [&] (
      AsyncWebSocket *server,
      AsyncWebSocketClient *client,
      AwsEventType type,
      void *arg,
      uint8_t *data,
      size_t len
    ) {
      OnWebSocketEvent(
        server,
        client,
        type,
        arg,
        data,
        len
      );
    }
  );
  Server->addHandler(WebSocket);
}

void EspWebSocket::OnWebSocketEvent(
  AsyncWebSocket *server,
  AsyncWebSocketClient *client,
  AwsEventType type,
  void *arg,
  uint8_t *data,
  size_t len
)
{
  if (type == WS_EVT_CONNECT) {
    PrintSerial->println("Websocket client connection received");
    WebSocketClient = client;
  }
  else if (type == WS_EVT_DISCONNECT) {
    PrintSerial->println("Websocket client connection finished");
    WebSocketClient = NULL;
  }
}

void EspWebSocket::Loop()
{
  uint32_t currentTime = millis();
  if (currentTime - PreviousWebSocketUpdate < WEB_SOCKET_UPDATE_DELAY) {
    return;
  }

  if (WebSocketClient != NULL && WebSocketClient->status() == WS_CONNECTED) {
    DynamicJsonDocument outputJson(10000);
    outputJson["Fm"] = Storage->FmChannelValuesContainer->GetJson();
    outputJson["Gyro"] = Storage->GyroValuesContainer->GetJson();
    outputJson["Motor"] = Storage->MotorsContainer->GetJson();
    String serializedJson;
    serializeJson(outputJson, serializedJson);
    WebSocketClient->text(
      serializedJson
    );
  }
  PreviousWebSocketUpdate = currentTime;
}