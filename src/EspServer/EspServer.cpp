#include "EspServer.h"

EspServer::EspServer(int serverPort, HardwareSerial *printSerial)
{
  PrintSerial = printSerial;
  Server = new AsyncWebServer(serverPort);
  FmChannelValuesJson = NULL_JSON;
  GyroValuesJson = NULL_JSON;
}

void EspServer::Setup()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Accept, Origin, Content-Type, Access-Control-Allow-Headers, X-Auth-Token, Authorization, X-Requested-With");

  Server->on(
    "/wifiConnect",
    HTTP_POST,
    [=](AsyncWebServerRequest * request) {
      request->send(200, JSON_CONTENT_TYPE, CONNECTED_JSON);
    },
    NULL,
    [=](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      std::string *serializedJson = new std::string((char *)data);
      DynamicJsonDocument wifiCredentials(120);
      deserializeJson(wifiCredentials, serializedJson->c_str());
      const char* ssid = wifiCredentials["ssid"];
      const char* password = wifiCredentials["password"];
      PrintSerial->println();
      PrintSerial->println("SSID: " + String(ssid));
      PrintSerial->println("Password: " + String(password));

      DynamicJsonDocument outputJson(120);
      outputJson["wifiConnectionStatus"] = ConnectToWifi(
        (char*)ssid,
        (char*)password
      );

      delete serializedJson;

      String outputSerializedJson;
      serializeJson(outputJson, outputSerializedJson);
      request->send(200, JSON_CONTENT_TYPE, outputSerializedJson);
    }
  );

  Server->on("/status", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, CONNECTED_JSON);
  });

  Server->on("/fm", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, FmChannelValuesJson);
  });

  Server->on("/gyro", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, GyroValuesJson);
  });

  Server->begin();
}

void EspServer::SetAccessPoint(char* ssid, char* password)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  PrintSerial->println("");
  PrintSerial->print("AP IP address: ");
  PrintSerial->println(myIP);
}

EspServer::WifiConnectionStatus EspServer::ConnectToWifi(char* ssid, char* password)
{
  if (!WifiSSID.isEmpty() && WifiSSID.equals(ssid)) {
    PrintSerial->println("");
    PrintSerial->print("Already connected to WiFi: ");
    PrintSerial->println(ssid);
    return WifiConnectionStatus::alreadyConnected;
  }

  if (WiFi.isConnected()) {
    if (WiFi.disconnect(true, false)) {
      PrintSerial->println("");
      PrintSerial->print("Disconnected: ");
      PrintSerial->println(WifiSSID);
      WifiSSID = "";
      WifiPassword = "";
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

  WifiSSID = String(ssid);
  WifiPassword = String(password);

  PrintSerial->println("");
  PrintSerial->println("WiFi connected.");
  PrintSerial->println("IP address: ");
  PrintSerial->println(WiFi.localIP());

  return WifiConnectionStatus::connected;
}