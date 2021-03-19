#include "ControllerApiResponse.h"

ControllerApiResponse::ControllerApiResponse(ControllerApiResponseKey responseKey, Json *jsonData)
{
  ResponseKey = responseKey;
  JsonData = jsonData;
}

ControllerApiResponse::~ControllerApiResponse()
{
  delete JsonData;
}