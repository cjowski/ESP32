#include "EspConnection.h"

EspConnection::EspConnection(bool connected)
{
  Connected = connected;
}

DynamicJsonDocument EspConnection::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["Connected"] = Connected;
  return outputJson;
}