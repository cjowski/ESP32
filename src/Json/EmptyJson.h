#ifndef EMPTY_JSON_H
#define EMPTY_JSON_H

  #include "Json/Json.h"

  class EmptyJson : public Json
  {
    public:
    int JSON_BUFFER_SIZE() const { return 0; };
    EmptyJson() { };
    DynamicJsonDocument GetJson() { return DynamicJsonDocument(JSON_BUFFER_SIZE()); };
    bool Equals(Json *otherJson) { return false; }
  };

#endif