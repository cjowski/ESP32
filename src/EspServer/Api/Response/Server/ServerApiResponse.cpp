#include "ServerApiResponse.h"

ServerApiResponse::ServerApiResponse(ResponseKey key, Json *jsonData)
{
  Key = key;
  JsonData = jsonData;
}

ServerApiResponse::~ServerApiResponse()
{
  delete JsonData;
}