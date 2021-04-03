#ifndef SERVER_API_RESPONSE_H
#define SERVER_API_RESPONSE_H

  #include "Json/Json.h"

  class ServerApiResponse
  {
    public:
    enum ResponseKey
    {
      WifiConnection,
      InvalidRequestKey
    };

    ResponseKey Key;
    Json *JsonData;

    ServerApiResponse(ResponseKey key, Json *jsonData);
    ~ServerApiResponse();
  };

#endif