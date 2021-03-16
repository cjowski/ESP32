#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

  #include "Json/Json.h"
  #include "EspServer/Utils/EspServerEnums.h"

  class WifiConnection : public Json
  {
    private:
    WifiConnectionStatus Status;

    public:
    int JSON_BUFFER_SIZE() const { return 20; };
    WifiConnection(WifiConnectionStatus status);
    WifiConnection(DynamicJsonDocument json);
    DynamicJsonDocument GetJson();
  };

#endif