#include "EspApi.h"

EspApi::EspApi(
  AsyncWebServer *server,
  EspServerStorage *storage,
  std::function<ServerApiResponse*(ServerApiRequest*)> sendRequestToServer,
  std::function<ControllerApiResponse*(ControllerApiRequest*)> sendRequestToController,
  bool debugMode
)
{
  Server = server;
  WebSocket = new EspWebSocket(server, storage, debugMode);
  Storage = storage;
  SendRequestToServer = sendRequestToServer;
  SendRequestToController = sendRequestToController;
  DebugMode = debugMode;
}

void EspApi::Setup()
{
  SetupHeaders();
  SetupWebHandlers();
  WebSocket->Setup();
}

void EspApi::SetupHeaders()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PATCH, PUT, DELETE, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Accept, Origin, Content-Type, Access-Control-Allow-Headers, X-Auth-Token, Authorization, X-Requested-With");
}

void EspApi::SetupWebHandlers()
{
  Server->on(
    "/wifiConnect",
    HTTP_POST,
    [=](AsyncWebServerRequest *request) { },
    NULL,
    [=](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
      std::string *serializedJson = new std::string((char*)data);

      ServerApiRequest *apiRequest = new ServerApiRequest(
        ServerApiRequest::ConnectToWifi,
        new WifiCredentials(
          serializedJson->c_str()
        )
      );

      ServerApiResponse *serverApiResponse = SendRequestToServer(
        apiRequest
      );

      String serverApiResponseJson = serverApiResponse->JsonData->GetSerializedJson();

      delete serializedJson;
      delete apiRequest;
      delete serverApiResponse;

      request->send(200, JSON_CONTENT_TYPE, serverApiResponseJson);
    }
  );

  Server->on("/status", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, EspConnection(true).GetSerializedJson());
  });

  Server->on("/fm", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, Storage->FmChannelValuesContainer->GetSerializedJson());
  });

  Server->on("/gyro", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, Storage->GyroValuesContainer->GetSerializedJson());
  });

  Server->on("/motor", HTTP_GET, [=](AsyncWebServerRequest *request) {
    request->send(200, JSON_CONTENT_TYPE, Storage->MotorsContainer->GetSerializedJson());
  });

  Server->on("/sayHiToStm", HTTP_GET, [=](AsyncWebServerRequest *request) {

    ControllerApiRequest *apiRequest = new ControllerApiRequest(
      ControllerApiRequest::SayHiToStm,
      new EmptyJson()
    );

    ControllerApiResponse *controllerApiResponse = SendRequestToController(
      apiRequest
    );

    String controllerApiResponseJson = controllerApiResponse->JsonData->GetSerializedJson();

    delete apiRequest;
    delete controllerApiResponse;

    request->send(200, JSON_CONTENT_TYPE, controllerApiResponseJson);
  });

  Server->on("/sayHiToStmStatus", HTTP_GET, [=](AsyncWebServerRequest *request) {
    
    request->hasParam("TaskID");
    int taskID = request->getParam("TaskID")->value().toInt();

    ControllerApiRequest *apiRequest = new ControllerApiRequest(
      ControllerApiRequest::SayHiToStmStatus,
      new IntegerJson(taskID)
    );

    ControllerApiResponse *controllerApiResponse = SendRequestToController(
      apiRequest
    );

    String controllerApiResponseJson = controllerApiResponse->JsonData->GetSerializedJson();

    delete apiRequest;
    delete controllerApiResponse;

    request->send(200, JSON_CONTENT_TYPE, controllerApiResponseJson);
  });
}

void EspApi::Loop()
{
  WebSocket->Loop();
}