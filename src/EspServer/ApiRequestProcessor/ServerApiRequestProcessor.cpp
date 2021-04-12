#include "ServerApiRequestProcessor.h"

ServerApiRequestProcessor::ServerApiRequestProcessor(
  std::function<WifiConnectionStatus(char *ssid, char *password)> connectToWifi
)
{
  ConnectToWifi = connectToWifi;
}

ServerApiResponse *ServerApiRequestProcessor::ProcessApiRequest(ServerApiRequest *apiRequest)
{
  if (apiRequest->Key == ServerApiRequest::ConnectToWifi) {
    WifiCredentials *wifiCredentials = (WifiCredentials*)(apiRequest->JsonData);
    WifiConnectionStatus status = ConnectToWifi(
      wifiCredentials->GetSSID(),
      wifiCredentials->GetPassword()
    );

    return new ServerApiResponse(
      ServerApiResponse::WifiConnection,
      new WifiConnection(status)
    );
  }

  return new ServerApiResponse(
    ServerApiResponse::InvalidRequestKey,
    new EmptyJson()
  );
}