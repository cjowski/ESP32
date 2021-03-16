#ifndef SERIAL_JSON_H
#define SERIAL_JSON_H

  #include "Json/Json.h"

  class SerialJson : Json
  {
    public:
    virtual char SerialPrintKey() const = 0;

    SerialJson() { };
    SerialJson(String serialReadText) { };
    
    virtual bool SerialReadTextValid(String serialReadText) = 0;
    DynamicJsonDocument GetJson();
    String GetSerializedJson() {
      String serializedJson;
      serializeJson(GetJson(), serializedJson);
      return serializedJson;
    };
  };

#endif