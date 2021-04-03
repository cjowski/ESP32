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
  MySerialReader = new SerialStringReader(&Serial2);
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
        millis(),
        new SerialPrinter(&Serial2, SERIAL_BAUD_RATE)
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
  MySerialReader->Read();
  MyEspServer->Storage.AddSerialValue(
    SerialValueInterpreter::GetSerialValueType(
      MySerialReader->GetRecentReadValue()
    ),
    MySerialReader->GetRecentReadValue()->ToString()
  );
  MyTaskController->Loop();
}