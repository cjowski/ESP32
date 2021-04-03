#include "SerialPrintValue.h"

SerialPrintValue::SerialPrintValue(int value)
{
  Value = value;
}

int SerialPrintValue::GetValue()
{
  return Value;
}