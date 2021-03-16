#include "SerialJsonContainer.h"

SerialJsonContainer::SerialJsonContainer(
  String name,
  std::list<SerialJson*> serialJsonList,
  size_t jsonBufferSize
)
{
  Name = name;
  SerialJsonList = serialJsonList;
  JsonBufferSize = jsonBufferSize;
}

SerialJsonContainer::~SerialJsonContainer()
{
  for(std::list<SerialJson*>::const_iterator it = SerialJsonList.begin(); it != SerialJsonList.end(); ++it)
  {
    delete *it;
  } 
  SerialJsonList.clear();
}

DynamicJsonDocument SerialJsonContainer::GetJson()
{
  DynamicJsonDocument outputJson(JsonBufferSize);
  JsonArray jsonArray = outputJson.createNestedArray(Name);

  std::list<SerialJson*>::iterator it;
  for (it = SerialJsonList.begin(); it != SerialJsonList.end(); it++)
  {
    jsonArray.add(
      (*it)->GetJson()
    );
  }

  return outputJson;
}

String SerialJsonContainer::GetSerializedJson()
{
  String serializedJson;
  serializeJson(GetJson(), serializedJson);
  return serializedJson;
}