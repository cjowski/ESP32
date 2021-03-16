#include "WifiConnection.h"

WifiConnection::WifiConnection(WifiConnectionStatus status)
{
  Status = status;
}

WifiConnection::WifiConnection(DynamicJsonDocument json)
{
  if (json.containsKey("Status"))
  {
    Status = static_cast<WifiConnectionStatus>(json["Status"]);
  }
  else {
    Status = WifiConnectionStatus::invalidJson;
  }
}

DynamicJsonDocument WifiConnection::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["Status"] = Status;
  return outputJson;
}