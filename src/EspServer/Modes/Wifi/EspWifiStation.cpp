#include "EspWifiStation.h"

EspWifiStation::EspWifiStation(HardwareSerial *printSerial)
{
  SSID = "";
  Password = "";
  PrintSerial = printSerial;
}

WifiConnectionStatus EspWifiStation::Connect(char* ssid, char* password)
{
  if (!SSID.isEmpty() && SSID.equals(ssid)) {
    PrintSerial->println("");
    PrintSerial->print("Already connected to WiFi: ");
    PrintSerial->println(ssid);
    return WifiConnectionStatus::alreadyConnected;
  }

  if (WiFi.isConnected()) {
    if (WiFi.disconnect(true, false)) {
      PrintSerial->println("");
      PrintSerial->print("Disconnected: ");
      PrintSerial->println(SSID);
      SSID = "";
      Password = "";
    }
  }

  PrintSerial->println("");
  PrintSerial->print("Connecting to ");
  PrintSerial->println(ssid);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    PrintSerial->println("");
    PrintSerial->println("WiFi connection failed.");
    return WifiConnectionStatus::connectionFailed;
  }

  SSID = String(ssid);
  Password = String(password);

  PrintSerial->println("");
  PrintSerial->println("WiFi connected.");
  PrintSerial->println("IP address: ");
  PrintSerial->println(WiFi.localIP());

  return WifiConnectionStatus::connected;
}