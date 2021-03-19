#ifndef SERVER_API_RESPONSE_H
#define SERVER_API_RESPONSE_H

  #include "Json/Json.h"

  class ServerApiResponse
  {
    public:
    enum ServerApiResponseKey
    {
      WifiConnection,
      InvalidRequestKey
    };

    ServerApiResponseKey ResponseKey;
    Json *JsonData;

    ServerApiResponse(ServerApiResponseKey responseKey, Json *jsonData);
    ~ServerApiResponse();
  };

#endif