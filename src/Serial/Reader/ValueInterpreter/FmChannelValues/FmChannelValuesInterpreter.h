#ifndef FM_CHANNEL_VALUES_INTERPRETER_H
#define FM_CHANNEL_VALUES_INTERPRETER_H

  #include <WString.h>
  #include "Serial/Reader/Value/SerialReadValue.h"

  class FmChannelValuesInterpreter
  {
    private:
    static const int SERIAL_TEXT_WORDS_COUNT = 6;
    static const char SERIAL_PRINT_KEY = 'F';

    public:
    static bool IsInteger(String text);
    static bool SerialReadValueMatched(SerialReadValue *serialReadValue);
  };

#endif