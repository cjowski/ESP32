#include "ServerApiRequest.h"

ServerApiRequest::ServerApiRequest(RequestKey key, Json *jsonData)
{
  Key = key;
  JsonData = jsonData;
}

ServerApiRequest::~ServerApiRequest()
{
  delete JsonData;
}