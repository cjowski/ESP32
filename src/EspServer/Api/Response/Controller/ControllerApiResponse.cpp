#include "ControllerApiResponse.h"

ControllerApiResponse::ControllerApiResponse(ResponseKey key, Json *jsonData)
{
  Key = key;
  JsonData = jsonData;
}

ControllerApiResponse::~ControllerApiResponse()
{
  delete JsonData;
}