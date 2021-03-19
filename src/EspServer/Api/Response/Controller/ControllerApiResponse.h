#ifndef CONTROLLER_API_RESPONSE_H
#define CONTROLLER_API_RESPONSE_H

  #include "Json/Json.h"

  class ControllerApiResponse
  {
    public:
    enum ControllerApiResponseKey
    {
      InvalidRequestKey
    };

    ControllerApiResponseKey ResponseKey;
    Json *JsonData;

    ControllerApiResponse(ControllerApiResponseKey responseKey, Json *jsonData);
    ~ControllerApiResponse();
  };

#endif