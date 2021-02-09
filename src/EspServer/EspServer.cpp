#include "EspServer.h"

EspServer::EspServer(int serverPort, HardwareSerial *printSerial)
{
  PrintSerial = printSerial;
  Server = new AsyncWebServer(serverPort);
  FmChannelValuesJson = "";
  GyroValuesJson = "";
}

void EspServer::Connect(char* ssid, char* password)
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Origin, Content-Type, X-Auth-Token");

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

  Server->on("/fm", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, FmChannelValuesJson);
  });

  Server->on("/gyro", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, GyroValuesJson);
  });

  Server->begin();
}