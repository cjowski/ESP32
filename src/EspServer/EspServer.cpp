#include "EspServer.h"

EspServer::EspServer(int serverPort, HardwareSerial *printSerial, String textContentType)
{
  PrintSerial = printSerial;
  Server = new AsyncWebServer(serverPort);
  TextContentType = textContentType;
  TextToSend = "";
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

  Server->on("/", HTTP_GET, [=](AsyncWebServerRequest *request) {
    OnClientGet(request);
  });

  Server->begin();
}

void EspServer::OnClientGet(AsyncWebServerRequest *request) {
  request->send(200, TextContentType, TextToSend);
}

void EspServer::SetTextToSend(String textToSend) {
  if (!textToSend.isEmpty())
  {
    TextToSend = textToSend;
  }
}