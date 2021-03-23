#include "JsonContainer.h"

JsonContainer::JsonContainer(String name, int maxListCount, int jsonListBufferSize)
{
  Name = name;
  MaxListCount = maxListCount;
  JsonListBufferSize = jsonListBufferSize;
}

void JsonContainer::AddToContainer(Json *newElement)
{
  if (Container.empty() || !Container.back()->Equals(newElement))
  {
    if (Container.size() == MaxListCount)
    {
      Json *frontElement = Container.front();
      Container.pop_front();
      delete frontElement;
    }

    Container.push_back(newElement);
  }
}

DynamicJsonDocument JsonContainer::GetJson()
{
  DynamicJsonDocument outputJson(JsonListBufferSize);
  JsonArray jsonArray = outputJson.createNestedArray(Name);

  std::list<Json*>::iterator it;
  for (it = Container.begin(); it != Container.end(); it++)
  {
    jsonArray.add(
      (*it)->GetJson()
    );
  }

  return outputJson;
}

String JsonContainer::GetSerializedJson() {
  String serializedJson;
  serializeJson(GetJson(), serializedJson);
  return serializedJson;
};