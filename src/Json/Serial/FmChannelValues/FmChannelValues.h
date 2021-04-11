#ifndef FM_CHANNEL_VALUES_H
#define FM_CHANNEL_VALUES_H

  #include "Json/Json.h"
  #include "Serial/Value/SerialValue.h"

  class FmChannelValues : public Json, public SerialValue
  {
    private:
    static const int CHANNELS_COUNT = 4;

    long Time;
    int FmSignalState;
    int ChannelValues[CHANNELS_COUNT];
    static bool IsInteger(String text);

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    int SERIAL_VALUES_COUNT() const { return CHANNELS_COUNT + 2; };
    char SERIAL_VALUE_KEY() const { return 'F'; };
    FmChannelValues() { };
    FmChannelValues(std::list<String> serialValues);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    std::list<String> GetPrintStrings();
  };

#endif