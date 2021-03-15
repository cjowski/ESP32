#include "EspServer.h"

EspServer::EspServer(int serverPort, HardwareSerial *printSerial)
{
  AccessPoint = new EspAccessPoint(printSerial);
  WifiStation = new EspWifiStation(printSerial);

  Api = new EspApi(
    serverPort,
    &Storage,
    printSerial,
    [&] (char* ssid, char* password) -> WifiConnectionStatus {
      return ConnectToWifi(ssid, password);
    }
  );

  PrintSerial = printSerial;
}

void EspServer::SetupApi()
{
  Api->Setup();
}

void EspServer::SetAccessPoint(char* ssid, char* password)
{
  AccessPoint->Connect(ssid, password);
}

WifiConnectionStatus EspServer::ConnectToWifi(char* ssid, char* password)
{
  return WifiStation->Connect(ssid, password);
}