#include "Json.h"

String Json::GetSerializedJson() {
  String serializedJson;
  serializeJson(GetJson(), serializedJson);
  return serializedJson;
};

String Json::GetProperty(DynamicJsonDocument json, String name)
{
  if (json.containsKey(name))
  {
    return String((const char*) json[name]);
  }
  return INVALID_PROPERTY;
}

DynamicJsonDocument Json::Deserialize(String serializedJson, int bufferSize) {
  DynamicJsonDocument deserializedJson(bufferSize);
  deserializeJson(deserializedJson, serializedJson);
  return deserializedJson;
}