#include "EspController.h"

EspController::EspController()
{
  MyTaskController = new TaskController();
}

void EspController::SetupSerials()
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  MySerialReader = new SerialReader(&Serial2);
}

void EspController::SetupServer(char *ssid, char *password, EspServer::Mode espMode)
{
  MyEspServer = new EspServer(
    ESP_SERVER_PORT,
    &Serial,
    [&] (ControllerApiRequest *apiRequest) -> ControllerApiResponse* {
      return ProcessApiRequest(apiRequest);
    }
  );

  switch (espMode)
  {
    case EspServer::Mode::accessPoint:
    {
      MyEspServer->SetAccessPoint(ssid, password);
      MyEspServer->SetupApi();
      break;
    }
    case EspServer::Mode::wifi:
    {
      MyEspServer->ConnectToWifi(ssid, password);
      MyEspServer->SetupApi();
      break;
    }
    default: {
      break;
    }
  }
}

ControllerApiResponse *EspController::ProcessApiRequest(ControllerApiRequest *apiRequest)
{
  if (apiRequest->Key == ControllerApiRequest::SayHiToStm)
  {
    SayHiToStmTask *sayHiToStmTask = new SayHiToStmTask(
      MyTaskController->GetNewTaskID(),
      millis(),
      new SerialPrinter(&Serial2)
    );

    MyTaskController->AddTask(sayHiToStmTask);

    return new ControllerApiResponse(
      ControllerApiResponse::TaskInitialized,
      new TaskStatus(
        sayHiToStmTask->ID,
        sayHiToStmTask->Done
      )
    );
  }
  else if (apiRequest->Key == ControllerApiRequest::SayHiToStmStatus)
  {
    SayHiToStmTask *sayHiToStmTask = (SayHiToStmTask*)MyTaskController->GetTaskWithID(
      ((IntegerJson*)(apiRequest->JsonData))->GetValue()
    );
    if (sayHiToStmTask != nullptr)
    {
      return new ControllerApiResponse(
        ControllerApiResponse::SayHiStmResponse,
        new SayHiStmResponse(
          sayHiToStmTask->GetStmGreeting(),
          sayHiToStmTask->ReceivedGreeting()
        )
      );
    }
  }

  return new ControllerApiResponse(
    ControllerApiResponse::InvalidRequestKey,
    new EmptyJson()
  );
}

void EspController::Setup(char *ssid, char *password, EspServer::Mode espMode)
{
  SetupSerials();
  SetupServer(ssid, password, espMode);
}

void EspController::Loop()
{
  ProcessSerialValue(
    MySerialReader->Read()
  );
  MyTaskController->Loop();
}

void EspController::ProcessSerialValue(UndefinedSerialValue serialValue)
{
  if (!serialValue.Exists())
  {
    return;
  }

  char readValueKey = serialValue.GetReadValueKey();
  std::list<String> serialValues = serialValue.GetPrintStrings();
  if (UndefinedSerialTask().SerialValueValid(readValueKey, serialValues))
  {
    ProcessSerialValueTask(
      UndefinedSerialTask(serialValue)
    );
    return;
  }
  else if (FmChannelValues().SerialValueValid(readValueKey, serialValues))
  {
    MyEspServer->Storage.AddFmChannelValues(
      new FmChannelValues(serialValues)
    );
  }
  else if (GyroValues().SerialValueValid(readValueKey, serialValues))
  {
    MyEspServer->Storage.AddGyroValues(
      new GyroValues(serialValues)
    );
  }
}

void EspController::ProcessSerialValueTask(UndefinedSerialTask serialTask)
{
  if (!MyTaskController->StmTaskProcessed(serialTask.GetTaskID()))
  {
    UndefinedSerialValue serialValue = serialTask.GetSerialValue();
    char readValueKey = serialValue.GetReadValueKey();
    std::list<String> serialValues = serialValue.GetPrintStrings();
    if (SayHiToEspMessage().SerialValueValid(readValueKey, serialValues))
    {
      SayHiToEspMessage sayHiToEspMessage = SayHiToEspMessage(serialValues);
      SayHiToStmTask *sayHiToStmTask = (SayHiToStmTask*)MyTaskController->GetTaskWithID(
        sayHiToEspMessage.GetEspTaskID()
      );
      if (sayHiToStmTask != nullptr)
      {
        sayHiToStmTask->SetStmGreeting(
          sayHiToEspMessage.GetGreeting()
        );
        Serial.println(sayHiToEspMessage.GetGreeting());
        MyTaskController->AddProcessedStmTaskID(serialTask.GetTaskID());
      }
    }
  }
}