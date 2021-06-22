#include "EspWifiStation.h"

EspWifiStation::EspWifiStation(bool debugMode)
{
  SSID = "";
  Password = "";
  DebugMode = debugMode;
}

WifiConnectionStatus EspWifiStation::Connect(char* ssid, char* password)
{
  if (!SSID.isEmpty() && SSID.equals(ssid)) {
    if (DebugMode)
    {
      Serial.println("");
      Serial.print("Already connected to WiFi: ");
      Serial.println(ssid);
    }
    return WifiConnectionStatus::alreadyConnected;
  }

  if (WiFi.isConnected()) {
    if (WiFi.disconnect(true, false)) {
      if (DebugMode)
      {
        Serial.println("");
        Serial.print("Disconnected: ");
        Serial.println(SSID);
      }
      SSID = "";
      Password = "";
    }
  }

  if (DebugMode)
  {
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    if (DebugMode)
    {
      Serial.println("");
      Serial.println("WiFi connection failed.");
    }
    return WifiConnectionStatus::connectionFailed;
  }

  SSID = String(ssid);
  Password = String(password);

  if (DebugMode)
  {
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  return WifiConnectionStatus::connected;
}