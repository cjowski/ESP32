#include "GyroValues.h"

GyroValues::GyroValues(String serialValue)
{
  int currentIndex = serialValue.indexOf(' ');
  Time = serialValue.substring(0, currentIndex).toInt();
  int previousIndex = currentIndex + 1;

  currentIndex = serialValue.indexOf(' ', currentIndex + 1);
  CalibrationDone = serialValue.substring(previousIndex, currentIndex).toInt() == 1;
  previousIndex = currentIndex + 1;

  currentIndex = serialValue.indexOf(' ', previousIndex + 1);
  Pitch = serialValue.substring(previousIndex, currentIndex).toFloat();
  previousIndex = currentIndex + 1;

  currentIndex = serialValue.indexOf(' ', previousIndex + 1);
  Roll = serialValue.substring(previousIndex, currentIndex).toFloat();
  previousIndex = currentIndex + 1;

  currentIndex = serialValue.indexOf(' ', previousIndex + 1);
  Yaw = serialValue.substring(previousIndex, currentIndex).toFloat();
}

bool GyroValues::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    if (!isDigit(text.charAt(i))) {
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

bool GyroValues::Equals(Json *otherJson)
{
  String otherTimeString = otherJson->GetProperty(otherJson->GetJson(), "Time");
  return IsInteger(otherTimeString) && Time == otherTimeString.toInt();
}