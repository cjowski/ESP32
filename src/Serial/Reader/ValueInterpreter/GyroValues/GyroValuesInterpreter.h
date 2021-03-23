#ifndef GYRO_VALUES_INTERPRETER_H
#define GYRO_VALUES_INTERPRETER_H

  #include <WString.h>
  #include "Serial/Reader/Value/SerialReadValue.h"

  class GyroValuesInterpreter
  {
    private:
    static const int SERIAL_TEXT_WORDS_COUNT = 5;
    static const char SERIAL_PRINT_KEY = 'G';

    public:
    static bool IsNumber(String text);
    static bool SerialReadValueMatched(SerialReadValue *serialReadValue);
  };

#endif