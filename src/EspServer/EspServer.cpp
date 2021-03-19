#include "EspServer.h"

EspServer::EspServer(
  int serverPort,
  HardwareSerial *printSerial,
  std::function<ControllerApiResponse*(ApiRequest*)> sendRequestToController
)
{
  AccessPoint = new EspAccessPoint(printSerial);
  WifiStation = new EspWifiStation(printSerial);

  Api = new EspApi(
    serverPort,
    &Storage,
    printSerial,
    [&] (ApiRequest *apiRequest) -> ServerApiResponse* {
      return ProcessApiRequest(apiRequest);
    },
    sendRequestToController
  );

  PrintSerial = printSerial;
  Storage = EspServerStorage();
}

void EspServer::SetAccessPoint(char *ssid, char *password)
{
  AccessPoint->Connect(ssid, password);
}

void EspServer::SetupApi()
{
  Api->Setup();
}

WifiConnectionStatus EspServer::ConnectToWifi(char *ssid, char *password)
{
  return WifiStation->Connect(ssid, password);
}

ServerApiResponse *EspServer::ProcessApiRequest(ApiRequest *apiRequest)
{
  if (apiRequest->RequestKey == ApiRequest::ConnectToWifi) {
    WifiCredentials *wifiCredentials = (WifiCredentials*)(apiRequest->JsonData);
    WifiConnectionStatus status = ConnectToWifi(
      wifiCredentials->GetSSID(),
      wifiCredentials->GetPassword()
    );

    return new ServerApiResponse(
      ServerApiResponse::WifiConnection,
      new WifiConnection(status)
    );
  }

  return new ServerApiResponse(
    ServerApiResponse::InvalidRequestKey,
    new EmptyJson()
  );
}