#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include "Serial/Reader/SerialReader.h"
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Task/TaskController/TaskController.h"
  #include "Task/UndefinedSerialTask.h"
  #include "EspController/Task/SayHiToStm/SayHiToStmTask.h"
  #include "Json/Serial/FmChannelValues/FmChannelValues.h"
  #include "Json/Serial/GyroValues/GyroValues.h"
  #include "Json/Serial/Motors/Motors.h"
  #include "Json/TaskStatus/TaskStatus.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"

  #define SERIAL2_RX_PIN 16
  #define SERIAL2_TX_PIN 17
  #define SERIAL_BAUD_RATE 19200
  #define SERIAL_SIZE_RX 512

  class SerialController
  {
    private:
    SerialReader *MySerialReader;
    TaskController *MyTaskController;
    EspServerStorage *Storage;

    public:
    SerialController(TaskController *taskController, EspServerStorage *storage);
    void Loop();
    void ProcessSerialValue(UndefinedSerialValue serialValue);
    void ProcessSerialValueTask(UndefinedSerialTask serialTask);
  };

#endif