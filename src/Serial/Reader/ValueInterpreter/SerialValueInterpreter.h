#ifndef SERIAL_VALUE_INTERPRETER_H
#define SERIAL_VALUE_INTERPRETER_H

  #include "Serial/Reader/ValueInterpreter/FmChannelValues/FmChannelValuesInterpreter.h"
  #include "Serial/Reader/ValueInterpreter/GyroValues/GyroValuesInterpreter.h"

  class SerialValueInterpreter
  {
    public:
    enum SerialValueType
    {
      FmChannelValuesJson,
      GyroValuesJson,
      None
    };
    static SerialValueType GetSerialValueType(SerialReadValue *serialReadValue);
  };

#endif