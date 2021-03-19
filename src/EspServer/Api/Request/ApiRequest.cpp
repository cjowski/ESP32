#include "ApiRequest.h"

ApiRequest::ApiRequest(ApiRequestKey requestKey, Json *jsonData)
{
  RequestKey = requestKey;
  JsonData = jsonData;
}

ApiRequest::~ApiRequest()
{
  delete JsonData;
}