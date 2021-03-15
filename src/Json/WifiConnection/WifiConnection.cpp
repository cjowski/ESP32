#include "WifiConnection.h"

WifiConnection::WifiConnection(WifiConnectionStatus status)
{
  Status = status;
}

DynamicJsonDocument WifiConnection::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE);
  outputJson["Status"] = Status;
  return outputJson;
}