#ifndef CONTROLLER_API_REQUEST_PROCESSOR_H
#define CONTROLLER_API_REQUEST_PROCESSOR_H

  #include <Serial/Type/StringList/Encoder/StringListEncoder.h>
  #include "Task/TaskController/TaskController.h"
  #include "EspServer/Api/Request/Controller/ControllerApiRequest.h"
  #include "EspServer/Api/Response/Controller/ControllerApiResponse.h"
  #include "Task/Type/SayHiToStm/SayHiToStmTask.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"
  #include "Json/TaskStatus/TaskStatus.h"
  #include "Json/EmptyJson.h"
  #include "Json/IntegerJson.h"

  #define SERIAL_BAUD_RATE 19200

  class ControllerApiRequestProcessor
  {
    private:
    TaskController *MyTaskController;

    public:
    ControllerApiRequestProcessor(TaskController *taskController);
    ControllerApiResponse *ProcessApiRequest(ControllerApiRequest *apiRequest);
  };

#endif