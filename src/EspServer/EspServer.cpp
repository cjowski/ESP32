#include "EspServer.h"

EspServer::EspServer(int serverPort, HardwareSerial *printSerial)
{
  AccessPoint = new EspAccessPoint(printSerial);
  WifiStation = new EspWifiStation(printSerial);

  Api = new EspApi(
    serverPort,
    &Storage,
    printSerial,
    [&] (EspApiRequest apiRequest) -> EspApiResponse {
      return ProcessApiRequest(apiRequest);
    }
  );

  PrintSerial = printSerial;
  Storage = EspServerStorage();
}

void EspServer::SetAccessPoint(char* ssid, char* password)
{
  AccessPoint->Connect(ssid, password);
}

void EspServer::SetupApi()
{
  Api->Setup();
}

WifiConnectionStatus EspServer::ConnectToWifi(char* ssid, char* password)
{
  return WifiStation->Connect(ssid, password);
}

EspApiResponse EspServer::ProcessApiRequest(EspApiRequest apiRequest)
{
  if (apiRequest.RequestKey == EspApiRequest::ConnectToWifi) {
    WifiCredentials wifiCredentials = WifiCredentials(apiRequest.JsonData);
    WifiConnectionStatus status = ConnectToWifi(
      wifiCredentials.GetSSID(),
      wifiCredentials.GetPassword()
    );

    return EspApiResponse {
      .ResponseKey = EspApiResponse::WifiConnection,
      .JsonData = WifiConnection(status).GetJson()
    };
  }

  return EspApiResponse {
    .ResponseKey = EspApiResponse::InvalidRequestKey,
    .JsonData = DynamicJsonDocument(0)
  };
}