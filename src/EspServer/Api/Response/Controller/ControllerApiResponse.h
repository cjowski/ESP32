#ifndef CONTROLLER_API_RESPONSE_H
#define CONTROLLER_API_RESPONSE_H

  #include "Json/Json.h"

  class ControllerApiResponse
  {
    public:
    enum ResponseKey
    {
      InvalidRequestKey,
      TaskInitialized,
      SayHiStmResponse
    };

    ResponseKey Key;
    Json *JsonData;

    ControllerApiResponse(ResponseKey key, Json *jsonData);
    ~ControllerApiResponse();
  };

#endif