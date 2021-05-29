#include "EspServer.h"

EspServer::EspServer(
  HardwareSerial *printSerial,
  std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController
)
{
  AccessPoint = new EspAccessPoint(printSerial);
  WifiStation = new EspWifiStation(printSerial);
  Server = new AsyncWebServer(ESP_SERVER_PORT);
  MyServerApiRequestProcessor = new ServerApiRequestProcessor(
    [&] (char *ssid, char *password) -> WifiConnectionStatus {
      return ConnectToWifi(ssid, password);
    }
  );

  Api = new EspApi(
    Server,
    &Storage,
    printSerial,
    [&] (ServerApiRequest *apiRequest) -> ServerApiResponse* {
      return MyServerApiRequestProcessor->ProcessApiRequest(apiRequest);
    },
    sendRequestToController
  );

  PrintSerial = printSerial;
  Storage = EspServerStorage();
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