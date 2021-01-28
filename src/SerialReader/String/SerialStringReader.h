#ifndef SERIAL_STRING_READER_H
#define SERIAL_STRING_READER_H

  #include "SerialReader/SerialReader.h"
  #include <WString.h>

  #define INPUT_STRING_SIZE 32

  class SerialStringReader : public SerialReader
  {
    public:
    SerialStringReader(HardwareSerial *readSerial) : SerialReader(readSerial) { };
    virtual void Read();
  };

#endif