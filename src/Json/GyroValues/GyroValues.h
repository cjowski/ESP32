#ifndef GYRO_VALUES_H
#define GYRO_VALUES_H

  #include <ArduinoJson.h>
  #include "Json/Serial/SerialJson.h"

  class GyroValues : public SerialJson
  {
    private:
    static const int SERIAL_TEXT_WORDS_COUNT = 5;

    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;
    static bool IsNumber(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    char SerialPrintKey() const { return 'G'; }
    GyroValues() { };
    GyroValues(String serialReadText);
    bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
  };

#endif