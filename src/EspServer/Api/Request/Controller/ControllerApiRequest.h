#ifndef CONTROLLER_API_REQUEST_H
#define CONTROLLER_API_REQUEST_H

  #include "Json/Json.h"

  class ControllerApiRequest
  {
    public:
    enum RequestKey
    {
      SayHiToStm
    };

    RequestKey Key;
    Json *JsonData;

    ControllerApiRequest(RequestKey key, Json *jsonData);
    ~ControllerApiRequest();
  };

#endif