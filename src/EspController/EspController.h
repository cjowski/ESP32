#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include <list>
  #include "EspServer/EspServer.h"
  #include "Serial/Reader/SerialReader.h"
  #include "Json/Serial/FmChannelValues/FmChannelValues.h"
  #include "Json/Serial/GyroValues/GyroValues.h"
  #include "EspController/Task/SayHiToStm/SayHiToStmTask.h"
  #include "Task/TaskController/TaskController.h"

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
    int NextTaskID = 1;

    void SetupSerials();
    void SetupServer(char *ssid, char *password, EspServer::Mode espMode);
    ControllerApiResponse *ProcessApiRequest(ControllerApiRequest *apiRequest);

    public:
    EspController();
    void Setup(char *ssid, char *password, EspServer::Mode espMode);
    void Loop();
    void AddSerialValueToStorage(UndefinedSerialValue serialValue);
  };
  
#endif