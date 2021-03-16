#ifndef JSON_H
#define JSON_H

  #include <ArduinoJson.h>

  class Json
  {
    public:
    Json() { };
    virtual ~Json() { };
    const String INVALID_PROPERTY = "INVALID_PROPERTY";
    virtual int JSON_BUFFER_SIZE() const = 0;
    
    virtual DynamicJsonDocument GetJson() = 0;
    
    String GetSerializedJson();
    String GetProperty(DynamicJsonDocument json, String name);
    DynamicJsonDocument Deserialize(String serializedJson, int bufferSize);
  };

#endif