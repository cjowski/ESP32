#include "FmChannelValuesContainer.h"

FmChannelValuesContainer::FmChannelValuesContainer(
  std::list<String> serialReadTextList,
  size_t jsonBufferSize
)
{
  std::list<String>::iterator it;
  for (it = serialReadTextList.begin(); it != serialReadTextList.end(); it++)
  {
    FmChannelValuesList.push_back(
      FmChannelValues(*it)
    );
  }
  JsonBufferSize = jsonBufferSize;
}

DynamicJsonDocument FmChannelValuesContainer::GetJson()
{
  DynamicJsonDocument outputJson(JsonBufferSize);
  JsonArray fmChannelValues = outputJson.createNestedArray("FmChannelValues");

  std::list<FmChannelValues>::iterator it;
  for (it = FmChannelValuesList.begin(); it != FmChannelValuesList.end(); it++)
  {
    fmChannelValues.add(
      FmChannelValues(*it).GetJson()
    );
  }

  return outputJson;
}

String FmChannelValuesContainer::GetSerializedJson()
{
  String serializedJson;
  serializeJson(GetJson(), serializedJson);
  return serializedJson;
}