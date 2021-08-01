#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include "EspServer/EspServer.h"
  #include "Serial/SerialController.h"
  #include "ApiRequestProcessor/ControllerApiRequestProcessor.h"
  #include "Oled/IpDisplayer/IpDisplayer.h"

  #define OLED_SCREEN_WIDTH 128
  #define OLED_SCREEN_HEIGHT 32

  class EspController
  {
    private:
    EspServer *MyEspServer;
    TaskController *MyTaskController;
    SerialController *MySerialController;
    ControllerApiRequestProcessor *MyControllerApiRequestProcessor;
    IpDisplayer *MyIpDisplayer;

    public:
    EspController();
    void ConnectServer(char *ssid, char *password, EspServer::Mode espMode);
    void Loop();
  };
  
#endif