#include "Motors.h"

Motors::Motors(StringListDecoderOutput *decoderOutput)
{
  std::list<String> texts = decoderOutput->GetTexts();
  auto it = texts.begin();
  Time = (*it).toInt();
  it++;
  for (int i = 0; i < MOTORS_COUNT; i++, it++)
  {
    MotorSpeed[i] = (*it).toInt();
  }
}

bool Motors::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isDigit(currentChar) && currentChar != '-') {
      return false;
    }
  }
  return true;
}

DynamicJsonDocument Motors::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());

  outputJson["Time"] = Time;
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    outputJson["MotorSpeed"][i] = MotorSpeed[i];
  }

  return outputJson;
}

bool Motors::Equals(Json *otherJson)
{
  String otherTimeString = otherJson->GetProperty(otherJson->GetJson(), "Time");
  return IsInteger(otherTimeString) && Time == otherTimeString.toInt();
}

bool Motors::SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput)
{
  StringListDecoderOutput *stringListDecoderOutput = (StringListDecoderOutput*)decoderOutput;

  if (stringListDecoderOutput->GetKey() != SERIAL_KEY
    || stringListDecoderOutput->GetTexts().size() != SERIAL_VALUES_COUNT
  )
  {
    return false;
  }

  std::list<String> texts = stringListDecoderOutput->GetTexts();
  for (auto it = texts.begin(); it != texts.end(); it++)
  {
    if (!IsInteger(*it))
    {
      return false;
    }
  }

  return true;
}