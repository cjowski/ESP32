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
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Origin, Content-Type, X-Auth-Token");

  Server->on("/wifiConnect", HTTP_POST, [=](AsyncWebServerRequest *request) {
    if (request->hasParam("ssid") && request->hasParam("password")) {
      ConnectToWifi(
        request->getParam("ssid")->value().c_str(),
        request->getParam("password")->value().c_str()
      );
    }
  });

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

void EspServer::SetAccessPoint(const char* ssid, const char* password)
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  PrintSerial->println("");
  PrintSerial->print("AP IP address: ");
  PrintSerial->println(myIP);
}

void EspServer::ConnectToWifi(const char* ssid, const char* password)
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