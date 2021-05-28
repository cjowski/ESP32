#ifndef ESP_SERVER_H
#define ESP_SERVER_H

  #include <WiFi.h>
  #include <HardwareSerial.h>
  #include <WString.h>
  #include "EspServer/Modes/AccessPoint/EspAccessPoint.h"
  #include "EspServer/Modes/Wifi/EspWifiStation.h"
  #include "EspServer/Api/EspApi.h"
  #include "EspServer/Storage/EspServerStorage.h"
  #include "ApiRequestProcessor/ServerApiRequestProcessor.h"

  #define ESP_SERVER_PORT 80

  class EspServer
  {
    private:
    EspAccessPoint *AccessPoint;
    EspWifiStation *WifiStation;
    EspApi *Api;
    ServerApiRequestProcessor *MyServerApiRequestProcessor;
    HardwareSerial *PrintSerial;
    EspServerStorage Storage;

    public:
    enum Mode {
      accessPoint,
      wifi
    };
    EspServer(
      HardwareSerial *printSerial,
      std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController
    );
    void Connect(char *ssid, char *password, EspServer::Mode espMode);
    void SetAccessPoint(char *ssid, char *password);
    void SetupApi();
    void Loop();
    WifiConnectionStatus ConnectToWifi(char *ssid, char *password);
    EspServerStorage *GetStorage();
  };

#endif