#include "EspServer.h"

EspServer::EspServer(
  std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController,
  bool debugMode
)
{
  AccessPoint = new EspAccessPoint(true);
  WifiStation = new EspWifiStation(true);
  Server = new AsyncWebServer(ESP_SERVER_PORT);
  MyServerApiRequestProcessor = new ServerApiRequestProcessor(
    [&] (char *ssid, char *password) -> WifiConnectionStatus {
      return ConnectToWifi(ssid, password);
    }
  );

  Api = new EspApi(
    Server,
    &Storage,
    [&] (ServerApiRequest *apiRequest) -> ServerApiResponse* {
      return MyServerApiRequestProcessor->ProcessApiRequest(apiRequest);
    },
    sendRequestToController,
    true
  );

  Storage = EspServerStorage();
  DebugMode = debugMode;
}

void EspServer::Connect(char *ssid, char *password, EspServer::Mode espMode)
{
  switch (espMode)
  {
    case EspServer::Mode::accessPoint:
    {
      SetAccessPoint(ssid, password);
      Setup();
      break;
    }
    case EspServer::Mode::wifi:
    {
      ConnectToWifi(ssid, password);
      Setup();
      break;
    }
    default: {
      break;
    }
  }
}

void EspServer::SetAccessPoint(char *ssid, char *password)
{
  AccessPoint->Connect(ssid, password);
}

void EspServer::Setup()
{
  Api->Setup();
  Server->begin();
}

void EspServer::Loop()
{
  Api->Loop();
}

WifiConnectionStatus EspServer::ConnectToWifi(char *ssid, char *password)
{
  return WifiStation->Connect(ssid, password);
}

EspServerStorage *EspServer::GetStorage()
{
  return &Storage;
}

String EspServer::GetAccessPointIp()
{
  return WiFi.softAPIP().toString();
}

String EspServer::GetWifiIp()
{
  return WiFi.localIP().toString();
}

String EspServer::GetWebSocketClientIp()
{
  return Api->GetWebSocketClientIp();
}