#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include <ArduinoJson.h>

  #define CHANNELS_COUNT 4
  #define JSON_BUFFER_SIZE 120
  
  const char WORD_SEPARATOR = ' ';

  class FmChannelValues
  {
    private:
    long Time;
    bool FmSignalActive;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    FmChannelValues(String serialReadText);
    static bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
    String GetSerializedJson();
  };

#endif