#ifndef GYRO_VALUES_H
#define GYRO_VALUES_H

  #include <Serial/Type/StringList/Decoder/StringListDecoderOutput.h>
  #include "Json/Json.h"

  class GyroValues : public Json
  {
    private:
    static const char SERIAL_KEY = 'G';
    static const int SERIAL_VALUES_COUNT = 5;

    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;
    static bool IsInteger(String text);
    static bool IsNumber(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    GyroValues() { };
    GyroValues(SerialDecoderOutput *decoderOutput) : GyroValues((StringListDecoderOutput*) decoderOutput) { };
    GyroValues(StringListDecoderOutput *decoderOutput);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    static bool SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput);
  };

#endif