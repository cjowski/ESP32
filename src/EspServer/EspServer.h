#ifndef ESP_SERVER_H
#define ESP_SERVER_H

  #include <WiFi.h>
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
    AsyncWebServer *Server;
    EspApi *Api;
    ServerApiRequestProcessor *MyServerApiRequestProcessor;
    EspServerStorage Storage;
    bool DebugMode = false;
    
    void Setup();

    public:
    enum Mode {
      accessPoint,
      wifi
    };
    EspServer(
      std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController,
      bool debugMode
    );
    void Connect(char *ssid, char *password, EspServer::Mode espMode);
    void SetAccessPoint(char *ssid, char *password);
    void Loop();
    WifiConnectionStatus ConnectToWifi(char *ssid, char *password);
    EspServerStorage *GetStorage();
    String GetAccessPointIp();
    String GetWifiIp();
    String GetWebSocketClientIp();
  };

#endif