#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include "Json/Json.h"

  class FmChannelValues : public Json
  {
    private:
    static const int CHANNELS_COUNT = 4;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    FmChannelValues() { };
    FmChannelValues(String serialValue);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
  };

#endif