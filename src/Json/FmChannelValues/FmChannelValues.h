#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include <ArduinoJson.h>

  #define CHANNELS_COUNT 4
  #define JSON_BUFFER_SIZE 100

  class FmChannelValues
  {
    private:
    long Time;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    FmChannelValues(String serialReadText);
    static bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
    String GetSerializedJson();
  };

#endif