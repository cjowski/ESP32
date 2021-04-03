#ifndef SERVER_API_REQUEST_H
#define SERVER_API_REQUEST_H

  #include "Json/Json.h"

  class ServerApiRequest
  {
    public:
    enum RequestKey
    {
      ConnectToWifi
    };

    RequestKey Key;
    Json *JsonData;

    ServerApiRequest(RequestKey key, Json *jsonData);
    ~ServerApiRequest();
  };

#endif