#ifndef FM_CHANNEL_VALUES_CONTAINER_H
#define FM_CHANNEL_VALUES_CONTAINER_H

  #include <ArduinoJson.h>
  #include <list>
  #include "FmChannelValues.h"

  #define CHANNELS_COUNT 4

  class FmChannelValuesContainer
  {
    private:
    std::list<FmChannelValues> FmChannelValuesList;
    size_t JsonBufferSize;

    public:
    FmChannelValuesContainer(std::list<String> serialReadTextList, size_t jsonBufferSize);
    DynamicJsonDocument GetJson();
    String GetSerializedJson();
  };

#endif