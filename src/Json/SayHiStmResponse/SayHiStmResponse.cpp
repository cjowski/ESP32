#include "SayHiStmResponse.h"

SayHiStmResponse::SayHiStmResponse()
{
  Exists = false;
}

SayHiStmResponse::SayHiStmResponse(String stmMessage)
{
  StmMessage = stmMessage;
  Exists = true;
}

DynamicJsonDocument SayHiStmResponse::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["StmMessage"] = StmMessage;
  return outputJson;
}