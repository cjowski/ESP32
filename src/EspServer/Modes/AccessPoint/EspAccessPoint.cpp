#include "EspAccessPoint.h"

EspAccessPoint::EspAccessPoint(HardwareSerial *printSerial)
{
  PrintSerial = printSerial;
}

void EspAccessPoint::Connect(char* ssid, char* password)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  PrintSerial->println("");
  PrintSerial->print("AP IP address: ");
  PrintSerial->println(myIP);
}