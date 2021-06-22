#include "FmChannelValues.h"

FmChannelValues::FmChannelValues(StringListDecoderOutput *decoderOutput)
{
  std::list<String> texts = decoderOutput->GetTexts();
  auto it = texts.begin();
  Time = (*it).toInt();
  it++;
  FmSignalState = (*it).toInt();
  it++;
  for (int i = 0; i < CHANNELS_COUNT; i++, it++)
  {
    ChannelValues[i] = (*it).toInt();
  }
}

bool FmChannelValues::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isDigit(currentChar) && currentChar != '-') {
      return false;
    }
  }
  return true;
}

DynamicJsonDocument FmChannelValues::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());

  outputJson["Time"] = Time;
  outputJson["FmSignalState"] = FmSignalState;
  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    outputJson["ChannelValues"][i] = ChannelValues[i];
  }

  return outputJson;
}

bool FmChannelValues::Equals(Json *otherJson)
{
  String otherTimeString = otherJson->GetProperty(otherJson->GetJson(), "Time");
  return IsInteger(otherTimeString) && Time == otherTimeString.toInt();
}

bool FmChannelValues::SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput)
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