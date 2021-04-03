#ifndef BOOLEAN_JSON_H
#define BOOLEAN_JSON_H

  #include "Json/Json.h"

  class BooleanJson : public Json
  {
    private:
    bool State;

    public:
    int JSON_BUFFER_SIZE() const { return 10; };
    BooleanJson(bool state) { State = state; };

    DynamicJsonDocument GetJson() {
      DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
      outputJson["State"] = State;
      return outputJson;
    };

    bool Equals(Json *otherJson) { return false; }
  };

#endif