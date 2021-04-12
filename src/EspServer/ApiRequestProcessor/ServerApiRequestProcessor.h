#ifndef SERVER_API_REQUEST_PROCESSOR_H
#define SERVER_API_REQUEST_PROCESSOR_H

  #include <functional>
  #include "EspServer/Api/Request/Server/ServerApiRequest.h"
  #include "EspServer/Api/Response/Server/ServerApiResponse.h"
  #include "Json/WifiConnection/WifiConnection.h"
  #include "Json/WifiCredentials/WifiCredentials.h"
  #include "Json/EmptyJson.h"

  class ServerApiRequestProcessor
  {
    private:
    std::function<WifiConnectionStatus(char *ssid, char *password)> ConnectToWifi;

    public:
    ServerApiRequestProcessor(
      std::function<WifiConnectionStatus(char *ssid, char *password)> connectToWifi
    );
    ServerApiResponse *ProcessApiRequest(ServerApiRequest *apiRequest);
  };

#endif