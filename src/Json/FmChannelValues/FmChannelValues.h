#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include <Serial/Type/StringList/Decoder/StringListDecoderOutput.h>
  #include "Json/Json.h"

  class FmChannelValues : public Json
  {
    private:
    static const int CHANNELS_COUNT = 4;
    static const char SERIAL_KEY = 'F';
    static const int SERIAL_VALUES_COUNT = 6;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    FmChannelValues() { };
    FmChannelValues(SerialDecoderOutput *decoderOutput) : FmChannelValues((StringListDecoderOutput*) decoderOutput) { };
    FmChannelValues(StringListDecoderOutput *decoderOutput);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    static bool SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput);
  };

#endif