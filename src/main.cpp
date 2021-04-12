#include <Arduino.h>
#include "EspController/EspController.h"

const char* SSID = "UPCCD6A9E8";
const char* PASSWORD = "tkr8QejnrMtr";

// const char* SSID = "CJ";
// const char* PASSWORD = "cjowski123";

// const char* SSID = "UPC240587058";
// const char* PASSWORD = "GZVXH92R";

EspController *espController = new EspController();

void setup() {
  espController->ConnectServer(
    (char*)SSID,
    (char*)PASSWORD,
    EspServer::Mode::wifi
  );
  delay(250);
}

void loop() {
  espController->Loop();
}