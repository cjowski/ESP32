#ifndef ESP_API_RESPONSE_H
#define ESP_API_RESPONSE_H

  #include <ArduinoJson.h>

  struct EspApiResponse
  {
    public:
    enum ApiResponseKey
    {
      WifiConnection,
      InvalidRequestKey
    };

    ApiResponseKey ResponseKey;
    DynamicJsonDocument JsonData;
  };

#endif