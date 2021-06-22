#ifndef ESP_ACCESS_POINT_H
#define ESP_ACCESS_POINT_H

  #include <WiFi.h>

  class EspAccessPoint
  {
    private:
    bool DebugMode = false;

    EspAccessPoint(bool debugMode);
    void Connect(char* ssid, char* password);

    friend class EspServer;
  };

#endif