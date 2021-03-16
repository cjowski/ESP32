#include "GyroValues.h"

GyroValues::GyroValues(String serialReadText)
{
  //STRING SHOULD BE VALIDATED BEFORE!!!
  int currentIndex = serialReadText.indexOf(' ');
  Time = serialReadText.substring(0, currentIndex).toInt();
  int previousIndex = currentIndex + 1;

  currentIndex = serialReadText.indexOf(' ', currentIndex + 1);
  CalibrationDone = serialReadText.substring(previousIndex, currentIndex).toInt() == 1;
  previousIndex = currentIndex + 1;

  currentIndex = serialReadText.indexOf(' ', previousIndex + 1);
  Pitch = serialReadText.substring(previousIndex, currentIndex).toFloat();
  previousIndex = currentIndex + 1;

  currentIndex = serialReadText.indexOf(' ', previousIndex + 1);
  Roll = serialReadText.substring(previousIndex, currentIndex).toFloat();
  previousIndex = currentIndex + 1;

  currentIndex = serialReadText.indexOf(' ', previousIndex + 1);
  Yaw = serialReadText.substring(previousIndex, currentIndex).toFloat();
}

bool GyroValues::IsNumber(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isDigit(currentChar) && currentChar != '.' && currentChar != '-') {
      return false;
    }
  }
  return true;
}

bool GyroValues::SerialReadTextValid(String serialReadText)
{
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
    
    if (!IsNumber(currentText))
    {
      return false;
    }
  }

  return true;
}

DynamicJsonDocument GyroValues::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());

  outputJson["Time"] = Time;
  outputJson["CalibrationDone"] = CalibrationDone;
  outputJson["Pitch"] = Pitch;
  outputJson["Roll"] = Roll;
  outputJson["Yaw"] = Yaw;

  return outputJson;
}