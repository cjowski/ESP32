#include "FmChannelValuesInterpreter.h"

bool FmChannelValuesInterpreter::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    if (!isdigit(text.charAt(i))) {
      return false;
    }
  }
  return true;
}

bool FmChannelValuesInterpreter::SerialReadValueMatched(SerialReadValue *serialReadValue)
{
  if (serialReadValue->GetSerialPrintKey() != SERIAL_PRINT_KEY)
  {
    return false;
  }

  String serialReadText = serialReadValue->ToString();
  int index = -1;
  String currentText = "";

  for (int i = 0; i < SERIAL_TEXT_WORDS_COUNT; i++)
  {
    index = serialReadText.indexOf(' ', i);

    if (index == -1)
    {
      return false;
    }

    if (i == 0)
    {
      currentText = serialReadText.substring(0, index);
    }
    else
    {
      currentText = serialReadText.substring(index - 1, index);
    }
    
    if (!IsInteger(currentText))
    {
      return false;
    }
  }

  return true;
}