#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include <ArduinoJson.h>
  #include "Json/SerialJson.h"

  class FmChannelValues : public SerialJson
  {
    private:
    static const int CHANNELS_COUNT = 4;
    static const int JSON_BUFFER_SIZE = 120;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    char SerialPrintKey() const { return 'F'; }
    FmChannelValues() { };
    FmChannelValues(String serialReadText);
    bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
  };

#endif