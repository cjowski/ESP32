#include "EspController.h"

EspController::EspController()
{
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  
  SerialPrinter *printer = new SerialPrinter(
    new StringListEncoder(false),
    &Serial2,
    SERIAL_BAUD_RATE
  );

  SerialReader *reader = new SerialReader(
    new StringListDecoder(false),
    &Serial2,
    SERIAL_BAUD_RATE
  );

  MyTaskController = new TaskController(printer, true);
  MyControllerApiRequestProcessor = new ControllerApiRequestProcessor(MyTaskController);
  MyEspServer = new EspServer(
    [&] (ControllerApiRequest *apiRequest) -> ControllerApiResponse* {
      return MyControllerApiRequestProcessor->ProcessApiRequest(apiRequest);
    },
    true
  );
  MySerialController = new SerialController(
    reader,
    MyTaskController,
    MyEspServer->GetStorage()
  );
  MyIpDisplayer = new IpDisplayer(
    OLED_SCREEN_WIDTH,
    OLED_SCREEN_HEIGHT,
    500,
    [&] () -> String {
      return MyEspServer->GetAccessPointIp();
    },
    [&] () -> String {
      return MyEspServer->GetWifiIp();
    }
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
  MyEspServer->Loop();
  MyIpDisplayer->Loop();
}