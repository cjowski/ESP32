#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include "Json/Serial/SerialJson.h"

  class FmChannelValues : public SerialJson
  {
    private:
    static const int CHANNELS_COUNT = 4;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    char SerialPrintKey() const { return 'F'; }
    FmChannelValues() { };
    FmChannelValues(String serialReadText);
    bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
  };

#endif