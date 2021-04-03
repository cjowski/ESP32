#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include <list>
  #include "EspServer/EspServer.h"
  #include "Serial/Reader/Read/String/SerialStringReader.h"
  #include "Serial/Reader/ValueInterpreter/SerialValueInterpreter.h"
  #include "Task/TaskController/TaskController.h"
  #include "EspController/Task/SayHiToStmTask.h"

  #define SERIAL2_RX_PIN 16
  #define SERIAL2_TX_PIN 17
  #define SERIAL_BAUD_RATE 19200
  #define SERIAL_SIZE_RX 512

  #define ESP_SERVER_PORT 80

  class EspController
  {
    private:
    SerialReader *MySerialReader;
    EspServer *MyEspServer;
    TaskController *MyTaskController;

    void SetupSerials();
    void SetupServer(char *ssid, char *password, EspServer::Mode espMode);
    ControllerApiResponse *ProcessApiRequest(ControllerApiRequest *apiRequest);

    public:
    EspController();
    void Setup(char *ssid, char *password, EspServer::Mode espMode);
    void Loop();
  };
  
#endif