#ifndef ESP_SERVER_H
#define ESP_SERVER_H

  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <HardwareSerial.h>
  #include <WString.h>

  class EspServer
  {
    private:
    const char* JSON_CONTENT_TYPE = "application/json";
    const char* CONNECTED_JSON = "{ \"connected\": true }";
    const char* NULL_JSON = "null";
    AsyncWebServer *Server;
    HardwareSerial *PrintSerial;

    public:
    String FmChannelValuesJson;
    String GyroValuesJson;
    EspServer(int serverPort, HardwareSerial *printSerial);
    void Setup();
    void SetAccessPoint(const char* ssid, const char* password);
    void ConnectToWifi(const char* ssid, const char* password);
  };

#endif