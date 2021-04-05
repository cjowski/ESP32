#include "FmChannelValues.h"

FmChannelValues::FmChannelValues(std::list<String> serialValues)
{
  auto it = serialValues.begin();
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

bool FmChannelValues::SerialValuesMatched(std::list<String> serialValues)
{
  if (serialValues.size() != SERIAL_VALUES_COUNT())
  {
    return false;
  }

  for (auto it = serialValues.begin(); it != serialValues.end(); it++)
  {
    if (!IsInteger(*it))
    {
      return false;
    }
  }

  return true;
}

std::list<String> FmChannelValues::GetPrintStrings()
{
  std::list<String> printStrings;
  return printStrings;
}