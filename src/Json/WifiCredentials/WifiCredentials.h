#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

  #include "Json/Json.h"

  class WifiCredentials : public Json
  {
    private:
    static const int JSON_BUFFER_SIZE = 120;
    String SSID;
    String Password;

    public:
    WifiCredentials(String ssid, String password);
    WifiCredentials(String serializedJson);
    DynamicJsonDocument GetJson();
    char* GetSSID();
    char* GetPassword();
  };

#endif