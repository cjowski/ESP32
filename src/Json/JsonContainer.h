#ifndef JSON_CONTAINER_H
#define JSON_CONTAINER_H

  #include <list>
  #include "Json/Json.h"

  class JsonContainer
  {
    private:
    std::list<Json*> Container;
    String Name;
    int MaxListCount;
    int JsonListBufferSize;

    public:
    JsonContainer(String name, int maxListCount, int jsonListBufferSize);
    void AddToContainer(Json *newElement);
    DynamicJsonDocument GetJson();
    String GetSerializedJson();
  };

#endif