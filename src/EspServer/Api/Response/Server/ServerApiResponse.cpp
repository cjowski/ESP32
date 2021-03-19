#include "ServerApiResponse.h"

ServerApiResponse::ServerApiResponse(ServerApiResponseKey responseKey, Json *jsonData)
{
  ResponseKey = responseKey;
  JsonData = jsonData;
}

ServerApiResponse::~ServerApiResponse()
{
  delete JsonData;
}