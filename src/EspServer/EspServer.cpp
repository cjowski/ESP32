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
      std::string *serializedJson = new std::string((char *)data); /* construct on the heap */
      PrintSerial->println(serializedJson->c_str());
      DynamicJsonDocument wifiCredentials(120);
      deserializeJson(wifiCredentials, serializedJson->c_str());
      const char* ssid = wifiCredentials["ssid"];
      const char* password = wifiCredentials["password"];
      PrintSerial->println("SSID: " + String(ssid));
      PrintSerial->println("Password: " + String(password));
      ConnectToWifi(
        (char*)ssid,
        (char*)password
      );
      delete serializedJson;
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

void EspServer::ConnectToWifi(char* ssid, char* password)
{
  PrintSerial->print("Connecting to ");
  PrintSerial->println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    PrintSerial->print(".");
  }

  PrintSerial->println("");
  PrintSerial->println("WiFi connected.");
  PrintSerial->println("IP address: ");
  PrintSerial->println(WiFi.localIP());
}