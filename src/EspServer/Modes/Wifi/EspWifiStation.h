#ifndef ESP_WIFI_STATION_H
#define ESP_WIFI_STATION_H

  #include <WiFi.h>
  #include <HardwareSerial.h>
  #include "EspServer/Utils/EspServerEnums.h"

  class EspWifiStation
  {
    private:
    String SSID;
    String Password;
    HardwareSerial *PrintSerial;

    EspWifiStation(HardwareSerial *printSerial);
    WifiConnectionStatus Connect(char* ssid, char* password);

    friend class EspServer;
  };

#endif