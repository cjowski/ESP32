#ifndef FM_SERIAL_JSON_CONTAINER_H
#define FM_SERIAL_JSON_CONTAINER_H

  #include <list>
  #include "SerialJson.h"

  class SerialJsonContainer
  {
    private:
    String Name;
    std::list<SerialJson*> SerialJsonList;
    size_t JsonBufferSize;

    public:
    SerialJsonContainer(
      String name,
      std::list<SerialJson*> serialJsonList,
      size_t jsonBufferSize
    );
    ~SerialJsonContainer();
    DynamicJsonDocument GetJson();
    String GetSerializedJson();
  };

#endif