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
    MyTaskController->AddTask(
      new SayHiToStmTask(
        NextTaskID++,
        millis(),
        new SerialPrinter(&Serial2)
      )
    );

    return new ControllerApiResponse(
      ControllerApiResponse::TaskInitialized,
      new BooleanJson(true)
    );
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
  AddSerialValueToStorage(
    MySerialReader->Read()
  );
  MyTaskController->Loop();
}

void EspController::AddSerialValueToStorage(UndefinedSerialValue serialValue)
{
  if (!serialValue.Exists())
  {
    return;
  }

  char readValueKey = serialValue.GetReadValueKey();
  std::list<String> serialValues = serialValue.GetPrintStrings();
  if (FmChannelValues().SerialValueValid(readValueKey, serialValues))
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