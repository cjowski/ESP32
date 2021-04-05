#include "GyroValues.h"

GyroValues::GyroValues(std::list<String> serialValues)
{
  auto it = serialValues.begin();
  Time = (*it).toInt();
  it++;
  CalibrationDone = (*it).toInt() == 1;
  it++;
  Pitch = (*it).toFloat();
  it++;
  Roll = (*it).toFloat();
  it++;
  Yaw = (*it).toFloat();
}

bool GyroValues::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    if (!isDigit(text.charAt(i))) {
      return false;
    }
  }
  return true;
}

bool GyroValues::IsNumber(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isdigit(currentChar) && currentChar != '.' && currentChar != '-') {
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

bool GyroValues::SerialValuesMatched(std::list<String> serialValues)
{
  if (serialValues.size() != SERIAL_VALUES_COUNT())
  {
    return false;
  }

  for (auto it = serialValues.begin(); it != serialValues.end(); it++)
  {
    if (!IsNumber(*it))
    {
      return false;
    }
  }

  return true;
}

std::list<String> GyroValues::GetPrintStrings()
{
  std::list<String> printStrings;
  return printStrings;
}