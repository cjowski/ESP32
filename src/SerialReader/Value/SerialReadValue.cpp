#include "SerialReadValue.h"

SerialReadValue::SerialReadValue()
{
  TextValue = "";
}

SerialReadValue SerialReadValue::GetCopy()
{
  SerialReadValue copy;
  copy.SetNewTextValue(SerialPrintKey, TextValue);
  return copy;
}

bool SerialReadValue::Equals(SerialReadValue valueToCompare)
{
  return TextValue.equals(valueToCompare.ToString());
}

void SerialReadValue::SetNewTextValue(char serialPrintKey, String newTextValue)
{
  SerialPrintKey = serialPrintKey;
  TextValue = newTextValue;
}

char SerialReadValue::GetSerialPrintKey()
{
  return SerialPrintKey;
}

String SerialReadValue::ToString()
{
  if (!TextValue.isEmpty())
  {
    return TextValue;
  }
  else
  {
    return (char *)"empty";
  }
}