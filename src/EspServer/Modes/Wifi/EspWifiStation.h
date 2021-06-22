#ifndef ESP_WIFI_STATION_H
#define ESP_WIFI_STATION_H

  #include <WiFi.h>
  #include "EspServer/Utils/EspServerEnums.h"

  class EspWifiStation
  {
    private:
    String SSID;
    String Password;
    bool DebugMode = false;

    EspWifiStation(bool debugMode);
    WifiConnectionStatus Connect(char* ssid, char* password);

    friend class EspServer;
  };

#endif