#include "EspServer.h"

EspServer::EspServer(
  HardwareSerial *printSerial,
  std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController
)
{
  AccessPoint = new EspAccessPoint(printSerial);
  WifiStation = new EspWifiStation(printSerial);
  MyServerApiRequestProcessor = new ServerApiRequestProcessor(
    [&] (char *ssid, char *password) -> WifiConnectionStatus {
      return ConnectToWifi(ssid, password);
    }
  );

  Api = new EspApi(
    ESP_SERVER_PORT,
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
      SetupApi();
      break;
    }
    case EspServer::Mode::wifi:
    {
      ConnectToWifi(ssid, password);
      SetupApi();
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

void EspServer::SetupApi()
{
  Api->Setup();
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