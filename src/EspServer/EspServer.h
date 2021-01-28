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
    AsyncWebServer *Server;
    HardwareSerial *PrintSerial;
    String TextToSend;
    String TextContentType;

    void OnClientGet(AsyncWebServerRequest *request);

    public:
    EspServer(int serverPort, HardwareSerial *printSerial, String textContentType);
    void Connect(char* ssid,  char* password);
    void SetTextToSend(String textToSend);
  };

#endif