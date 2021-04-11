#include "SayHiStmResponse.h"

SayHiStmResponse::SayHiStmResponse(String greeting, bool done)
{
  Greeting = greeting;
  Done = done;
}

DynamicJsonDocument SayHiStmResponse::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["Greeting"] = Greeting;
  outputJson["Done"] = Done;
  return outputJson;
}