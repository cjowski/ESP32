#ifndef ESP_API_REQUEST_H
#define ESP_API_REQUEST_H

  #include <ArduinoJson.h>

  struct EspApiRequest
  {
    public:
    enum ApiRequestKey
    {
      ConnectToWifi
    };

    ApiRequestKey RequestKey;
    DynamicJsonDocument JsonData;
  };

#endif