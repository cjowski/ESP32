#include "WifiCredentials.h"

WifiCredentials::WifiCredentials(String ssid, String password)
{
  SSID = ssid;
  Password = password;
}

WifiCredentials::WifiCredentials(DynamicJsonDocument json)
{
  SSID = GetProperty(json, "SSID");
  Password = GetProperty(json, "Password");
}

WifiCredentials::WifiCredentials(String serializedJson)
{
  DynamicJsonDocument json = Deserialize(serializedJson, JSON_BUFFER_SIZE());
  SSID = GetProperty(json, "SSID");
  Password = GetProperty(json, "Password");
}

DynamicJsonDocument WifiCredentials::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["SSID"] = SSID;
  outputJson["Password"] = Password;
  return outputJson;
}

char* WifiCredentials::GetSSID()
{
  return (char*)SSID.c_str();
}

char* WifiCredentials::GetPassword()
{
  return (char*)Password.c_str();
}