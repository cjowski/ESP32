#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include <list>
  #include <ArduinoJson.h>
  #include "Json/SerialJson.h"

  class FmChannelValues : public SerialJson
  {
    private:
    static const int CHANNELS_COUNT = 4;
    static const int JSON_BUFFER_SIZE = 120;

    long Time;
    bool FmSignalActive;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    static const char SERIAL_PRINT_KEY = 'F';
    FmChannelValues(String serialReadText);
    static bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
  };

#endif