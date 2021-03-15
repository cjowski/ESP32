#ifndef JSON_H
#define JSON_H

  #include <ArduinoJson.h>

  class Json
  {
    public:
    Json() { };
    virtual ~Json() { };
    
    virtual DynamicJsonDocument GetJson() = 0;
    
    String GetSerializedJson();
    String GetProperty(DynamicJsonDocument json, String name);
    DynamicJsonDocument Deserialize(String serializedJson, int bufferSize);
  };

#endif