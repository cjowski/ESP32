#include "FmChannelValues.h"

FmChannelValues::FmChannelValues(String serialValue)
{
  int currentIndex = serialValue.indexOf(' ');
  Time = serialValue.substring(0, currentIndex).toInt();
  int previousIndex = currentIndex + 1;

  currentIndex = serialValue.indexOf(' ', previousIndex + 1);
  FmSignalState = serialValue.substring(previousIndex, currentIndex).toInt();
  previousIndex = currentIndex + 1;

  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    currentIndex = serialValue.indexOf(' ', previousIndex + 1);
    ChannelValues[i] = serialValue.substring(previousIndex, currentIndex).toInt();
    previousIndex = currentIndex + 1;
  }
}

bool FmChannelValues::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    if (!isDigit(text.charAt(i))) {
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