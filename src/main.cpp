#include <Arduino.h>
#include "EspController/EspController.h"

const char* SSID = "UPCCD6A9E8";
const char* PASSWORD = "tkr8QejnrMtr";

EspController *espController = new EspController();

void setup() {
  espController->Setup((char*)SSID, (char*)PASSWORD);
  delay(250);
}

void loop() {
  espController->Loop();
}