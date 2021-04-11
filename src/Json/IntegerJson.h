#ifndef INTEGER_JSON_H
#define INTEGER_JSON_H

  #include "Json/Json.h"

  class IntegerJson : public Json
  {
    private:
    int Value;

    public:
    int JSON_BUFFER_SIZE() const { return 10; };
    IntegerJson(int value) { Value = value; };

    DynamicJsonDocument GetJson() {
      DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
      outputJson["Value"] = Value;
      return outputJson;
    };

    int GetValue() { return Value; }
    bool Equals(Json *otherJson) { return false; }
  };

#endif