#include "SerialReadValue.h"

SerialReadValue::SerialReadValue()
{
  TextValue = "";
}

SerialReadValue SerialReadValue::GetCopy()
{
  SerialReadValue copy;
  copy.SetNewTextValue(TextValue);
  return copy;
}

bool SerialReadValue::Equals(SerialReadValue valueToCompare)
{
  return TextValue.equals(valueToCompare.GetText());
}

void SerialReadValue::SetNewTextValue(String newTextValue)
{
  TextValue = newTextValue;
}

String SerialReadValue::GetText()
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