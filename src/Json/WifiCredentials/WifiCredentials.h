#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

  #include "Json/Json.h"

  class WifiCredentials : public Json
  {
    private:
    String SSID;
    String Password;

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    WifiCredentials(String ssid, String password);
    WifiCredentials(DynamicJsonDocument json);
    WifiCredentials(String serializedJson);
    DynamicJsonDocument GetJson();
    char* GetSSID();
    char* GetPassword();
  };

#endif