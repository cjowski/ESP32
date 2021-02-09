#ifndef GYRO_VALUES_H
#define GYRO_VALUES_H

  #include <list>
  #include <ArduinoJson.h>
  #include "Json/SerialJson.h"

  class GyroValues : public SerialJson
  {
    private:
    static const int SERIAL_TEXT_WORDS_COUNT = 5;
    static const int JSON_BUFFER_SIZE = 120;

    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;
    static bool IsNumber(String text);

    public:
    static const char SERIAL_PRINT_KEY = 'G';
    GyroValues(String serialReadText);
    static bool SerialReadTextValid(String serialReadText);
    DynamicJsonDocument GetJson();
  };

#endif