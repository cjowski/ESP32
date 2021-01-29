#ifndef SERIAL_STRING_READER_H
#define SERIAL_STRING_READER_H

  #include "SerialReader/SerialReader.h"
  #include <WString.h>

  #define INPUT_STRING_SIZE 50

  class SerialStringReader : public SerialReader
  {
    private:
    char ReceivedChars[INPUT_STRING_SIZE];
    const char START_MARKER = '<';
    const char END_MARKER = '>';
    const char FIRST_WORD_SEPARATOR = 'A';

    bool IsWordSeparator(char character);
    void SetReceivedChar(char character, int index);

    public:
    SerialStringReader(HardwareSerial *readSerial) : SerialReader(readSerial) { };
    virtual void Read();
  };

#endif