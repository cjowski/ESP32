#include "ControllerApiRequest.h"

ControllerApiRequest::ControllerApiRequest(RequestKey key, Json *jsonData)
{
  Key = key;
  JsonData = jsonData;
}

ControllerApiRequest::~ControllerApiRequest()
{
  delete JsonData;
}