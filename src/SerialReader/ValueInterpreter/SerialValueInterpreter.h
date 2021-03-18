#ifndef SERIAL_VALUE_INTERPRETER_H
#define SERIAL_VALUE_INTERPRETER_H

  #include "SerialReader/Value/SerialReadValue.h"
  #include "SerialReader/ValueInterpreter/FmChannelValues/FmChannelValuesInterpreter.h"
  #include "SerialReader/ValueInterpreter/GyroValues/GyroValuesInterpreter.h"

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