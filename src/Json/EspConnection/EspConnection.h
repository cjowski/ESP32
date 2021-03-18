#ifndef ESP_CONNECTION_H
#define ESP_CONNECTION_H

  #include "Json/Json.h"

  class EspConnection : public Json
  {
    private:
    bool Connected;

    public:
    int JSON_BUFFER_SIZE() const { return 20; };
    EspConnection(bool connected);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson) { return true; } //TODO
  };

#endif