#include <Arduino.h>
#include "EspController/EspController.h"

// const char* SSID = "UPCCD6A9E8";
// const char* PASSWORD = "tkr8QejnrMtr";

const char* SSID = "CJ";
const char* PASSWORD = "cjowski123";

EspController *espController = new EspController();

void setup() {
  espController->Setup(
    SSID,
    PASSWORD,
    EspController::Mode::accessPoint
  );
  delay(250);
}

void loop() {
  espController->Loop();
}