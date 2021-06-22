#include "EspAccessPoint.h"

EspAccessPoint::EspAccessPoint(bool debugMode)
{
  DebugMode = debugMode;
}

void EspAccessPoint::Connect(char* ssid, char* password)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  if (DebugMode)
  {
    Serial.println("");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
}