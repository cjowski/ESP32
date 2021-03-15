#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

  #include "Json/Json.h"
  #include "EspServer/Utils/EspServerEnums.h"

  class WifiConnection : public Json
  {
    private:
    static const int JSON_BUFFER_SIZE = 20;
    WifiConnectionStatus Status;

    public:
    WifiConnection(WifiConnectionStatus status);
    DynamicJsonDocument GetJson();
  };

#endif