#ifndef ESP_CONNECTION_H
#define ESP_CONNECTION_H

  #include "Json/Json.h"

  class EspConnection : public Json
  {
    private:
    static const int JSON_BUFFER_SIZE = 20;
    bool Connected;

    public:
    EspConnection(bool connected);
    DynamicJsonDocument GetJson();
  };

#endif