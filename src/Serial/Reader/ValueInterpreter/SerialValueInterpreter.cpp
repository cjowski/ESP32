#include "SerialValueInterpreter.h"

SerialValueInterpreter::SerialValueType SerialValueInterpreter::GetSerialValueType(
  SerialReadValue *serialReadValue
)
{
  if (FmChannelValuesInterpreter::SerialReadValueMatched(serialReadValue))
  {
    return SerialValueInterpreter::FmChannelValuesJson;
  }
  else if (GyroValuesInterpreter::SerialReadValueMatched(serialReadValue))
  {
    return SerialValueInterpreter::GyroValuesJson;
  }
  return SerialValueInterpreter::None;
}