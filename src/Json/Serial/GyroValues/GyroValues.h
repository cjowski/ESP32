#ifndef GYRO_VALUES_H
#define GYRO_VALUES_H

  #include "Json/Json.h"

  class GyroValues : public Json
  {
    private:
    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;
    static bool IsInteger(String text);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    GyroValues() { };
    GyroValues(String serialValue);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
  };

#endif