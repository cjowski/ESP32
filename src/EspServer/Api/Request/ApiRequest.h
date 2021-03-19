#ifndef ESP_API_REQUEST_H
#define ESP_API_REQUEST_H

  #include "Json/Json.h"

  class ApiRequest
  {
    public:
    enum ApiRequestKey
    {
      ConnectToWifi
    };

    ApiRequestKey RequestKey;
    Json *JsonData;

    ApiRequest(ApiRequestKey requestKey, Json *jsonData);
    ~ApiRequest();
  };

#endif