#include "EspController.h"

EspController::EspController()
{
  MyTaskController = new TaskController();
  MyControllerApiRequestProcessor = new ControllerApiRequestProcessor(MyTaskController);
  MyEspServer = new EspServer(
    &Serial,
    [&] (ControllerApiRequest *apiRequest) -> ControllerApiResponse* {
      return MyControllerApiRequestProcessor->ProcessApiRequest(apiRequest);
    }
  );
  MySerialController = new SerialController(
    MyTaskController,
    MyEspServer->GetStorage()
  );
}

void EspController::ConnectServer(char *ssid, char *password, EspServer::Mode espMode)
{
  MyEspServer->Connect(ssid, password, espMode);
}

void EspController::Loop()
{
  MySerialController->Loop();
  MyTaskController->Loop();
}