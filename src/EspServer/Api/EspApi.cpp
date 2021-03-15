#include "EspApi.h"

EspApi::EspApi(
  int serverPort,
  EspServerStorage *storage,
  HardwareSerial *printSerial,
  std::function<WifiConnectionStatus(char*, char*)> connectToWifiCallback
)
{
  Server = new AsyncWebServer(serverPort);
  Storage = storage;
  PrintSerial = printSerial;
  ConnectToWifi = connectToWifiCallback;
}

void EspApi::Setup()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Accept, Origin, Content-Type, Access-Control-Allow-Headers, X-Auth-Token, Authorization, X-Requested-With");

  Server->on(
    "/wifiConnect",
    HTTP_POST,
    [=](AsyncWebServerRequest *request) { },
    NULL,
    [=](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      std::string *serializedJson = new std::string((char*)data);

      WifiCredentials wifiCredentials = WifiCredentials(
        serializedJson->c_str()
      );

      WifiConnectionStatus status = ConnectToWifi(
        wifiCredentials.GetSSID(),
        wifiCredentials.GetPassword()
      );

      delete serializedJson;

      request->send(200, JSON_CONTENT_TYPE, WifiConnection(status).GetSerializedJson());
    }
  );

  Server->on("/status", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, EspConnection(true).GetSerializedJson());
  });

  Server->on("/fm", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, Storage->FmChannelValuesJson);
  });

  Server->on("/gyro", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, Storage->GyroValuesJson);
  });

  Server->begin();
}