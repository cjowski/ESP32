#ifndef ESP_ACCESS_POINT_H
#define ESP_ACCESS_POINT_H

  #include <WiFi.h>
  #include <HardwareSerial.h>

  class EspAccessPoint
  {
    private:
    HardwareSerial *PrintSerial;
    EspAccessPoint(HardwareSerial *printSerial);
    void Connect(char* ssid, char* password);

    friend class EspServer;
  };

#endif