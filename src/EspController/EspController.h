#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include "EspServer/EspServer.h"
  #include "Serial/SerialController.h"
  #include "ApiRequestProcessor/ControllerApiRequestProcessor.h"

  class EspController
  {
    private:
    EspServer *MyEspServer;
    TaskController *MyTaskController;
    SerialController *MySerialController;
    ControllerApiRequestProcessor *MyControllerApiRequestProcessor;

    public:
    EspController();
    void ConnectServer(char *ssid, char *password, EspServer::Mode espMode);
    void Loop();
  };
  
#endif