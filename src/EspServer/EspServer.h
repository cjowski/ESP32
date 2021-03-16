#ifndef ESP_SERVER_H
#define ESP_SERVER_H

  #include <WiFi.h>
  #include <HardwareSerial.h>
  #include <WString.h>
  #include "EspServer/Modes/AccessPoint/EspAccessPoint.h"
  #include "EspServer/Modes/Wifi/EspWifiStation.h"
  #include "EspServer/Api/EspApi.h"
  #include "EspServer/Storage/EspServerStorage.h"

  class EspServer
  {
    private:
    EspAccessPoint *AccessPoint;
    EspWifiStation *WifiStation;
    EspApi *Api;
    HardwareSerial *PrintSerial;

    public:
    enum Mode {
      accessPoint,
      wifi
    };
    EspServerStorage Storage;
    EspServer(int serverPort, HardwareSerial *printSerial);
    void SetAccessPoint(char* ssid, char* password);
    void SetupApi();
    EspApiResponse ProcessApiRequest(EspApiRequest apiRequest);
    WifiConnectionStatus ConnectToWifi(char* ssid, char* password);
  };

#endif