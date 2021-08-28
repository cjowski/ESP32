#include "EspWebSocket.h"

EspWebSocket::EspWebSocket(
  AsyncWebServer *server,
  EspServerStorage *storage,
  bool debugMode
)
{
  Server = server;
  WebSocket = new AsyncWebSocket(WEB_SOCKET_URL);
  Storage = storage;
  DebugMode = debugMode;
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
    WebSocketClient = client;
    if (DebugMode) {
      Serial.print("Websocket client connection received: ");
      Serial.println(GetClientIp());
    }
  }
  else if (type == WS_EVT_DISCONNECT) {
    WebSocketClient = NULL;
    if (DebugMode) {
      Serial.println("Websocket client connection finished");
    }
  }
}

String EspWebSocket::GetClientIp()
{
  if (WebSocketClient == NULL) {
    return "";
  }
  return WebSocketClient->remoteIP().toString();
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