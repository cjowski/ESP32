#include "FmChannelValues.h"

FmChannelValues::FmChannelValues(String serialReadText)
{
  //STRING SHOULD BE VALIDATED BEFORE!!!
  int currentIndex = serialReadText.indexOf(WORD_SEPARATOR);
  Time = serialReadText.substring(0, currentIndex).toInt();
  int previousIndex = currentIndex + 1;
  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    currentIndex = serialReadText.indexOf(WORD_SEPARATOR, previousIndex + 1);
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

  for (int i = 0; i < CHANNELS_COUNT + 1; i++)
  {
    index = serialReadText.indexOf(WORD_SEPARATOR, i);

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
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE);

  outputJson["Time"] = Time;
  for (int i = 0; i < CHANNELS_COUNT; i++)
  {
    outputJson["ChannelValues"][i] = ChannelValues[i];
  }

  return outputJson;
}

String FmChannelValues::GetSerializedJson()
{
  String serializedJson;
  serializeJson(GetJson(), serializedJson);
  return serializedJson;
}