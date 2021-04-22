#ifndef MOTORS_H
#define MOTORS_H

  #include "Json/Json.h"
  #include "Serial/Value/SerialValue.h"

  class Motors : public Json, public SerialValue
  {
    private:
    static const int MOTORS_COUNT = 4;
    long Time;
    int MotorSpeed[MOTORS_COUNT];
    static bool IsInteger(String text);

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    int JSON_BUFFER_SIZE() const { return 120; };
    int SERIAL_VALUES_COUNT() const { return MOTORS_COUNT + 1; };
    char SERIAL_VALUE_KEY() const { return 'M'; };
    Motors() { };
    Motors(std::list<String> serialValues);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson);
    std::list<String> GetPrintStrings();
  };

#endif