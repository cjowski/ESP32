#ifndef GYRO_VALUES_H
#define GYRO_VALUES_H

  #include "Json/Json.h"
  #include "Serial/Value/SerialValue.h"

  class GyroValues : public Json, public SerialValue
  {
    private:
    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;
    static bool IsInteger(String text);
    static bool IsNumber(String text);

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    int SERIAL_VALUES_COUNT() const { return 5; };
    char SERIAL_VALUE_KEY() const { return 'G'; };
    GyroValues() { };
    GyroValues(std::list<String> serialValues);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    std::list<String> GetPrintStrings();
  };

#endif