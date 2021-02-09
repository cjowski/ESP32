#ifndef SERIAL_JSON_H
#define SERIAL_JSON_H

  #include <ArduinoJson.h>

  class SerialJson
  {
    public:
    SerialJson() { };
    virtual ~SerialJson() { };
    SerialJson(String serialReadText) { };
    
    virtual DynamicJsonDocument GetJson() = 0;
    String GetSerializedJson() {
      String serializedJson;
      serializeJson(GetJson(), serializedJson);
      return serializedJson;
    };
  };

#endif