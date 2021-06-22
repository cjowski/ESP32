#ifndef MOTORS_H
#define MOTORS_H

  #include <Serial/Type/StringList/Decoder/StringListDecoderOutput.h>
  #include "Json/Json.h"

  class Motors : public Json
  {
    private:
    static const int MOTORS_COUNT = 4;
    static const char SERIAL_KEY = 'M';
    static const int SERIAL_VALUES_COUNT = 5;

    long Time;
    int MotorSpeed[MOTORS_COUNT];
    static bool IsInteger(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    Motors() { };
    Motors(SerialDecoderOutput *decoderOutput) : Motors((StringListDecoderOutput*) decoderOutput) { };
    Motors(StringListDecoderOutput *decoderOutput);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    static bool SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput);
  };

#endif