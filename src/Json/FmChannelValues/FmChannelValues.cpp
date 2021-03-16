#include "FmChannelValues.h"

FmChannelValues::FmChannelValues(String serialReadText)
{
  //STRING SHOULD BE VALIDATED BEFORE!!!
  int currentIndex = serialReadText.indexOf(' ');
  Time = serialReadText.substring(0, currentIndex).toInt();
  int previousIndex = currentIndex + 1;

  currentIndex = serialReadText.indexOf(' ', previousIndex + 1);
  FmSignalState = serialReadText.substring(previousIndex, currentIndex).toInt();
  previousIndex = currentIndex + 1;

  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    currentIndex = serialReadText.indexOf(' ', previousIndex + 1);
    ChannelValues[i] = serialReadText.substring(previousIndex, currentIndex).toInt();
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

bool FmChannelValues::SerialReadTextValid(String serialReadText)
{
  int index = -1;
  String currentText = "";

  for (int i = 0; i < CHANNELS_COUNT + 2; i++)
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