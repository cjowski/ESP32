#include "SayHiToEspMessage.h"

SayHiToEspMessage::SayHiToEspMessage(std::list<String> serialValues)
{
  auto it = serialValues.begin();
  TaskID = (*it).toInt();
  it++;
  it++;
  EspTaskID = (*it).toInt();
  it++;
  Greeting = *it;
}

bool SayHiToEspMessage::IsInteger(String text) {
  for(char i = 0; i < text.length(); i++) {
    char currentChar = text.charAt(i);
    if (!isdigit(currentChar) && currentChar != '-') {
      return false;
    }
  }
  return true;
}

bool SayHiToEspMessage::SerialValuesMatched(std::list<String> serialValues)
{
  if (serialValues.size() != SERIAL_VALUES_COUNT())
  {
    return false;
  }

  auto it = serialValues.begin();
  if (!IsInteger(*it) && (*it).toInt() > 0)
  {
    return false;
  }

  it++;
  if (!IsInteger(*it) && (*it).toInt() != EspTask::SayHiToEsp)
  {
    return false;
  }

  it++;
  if (!IsInteger(*it) && (*it).toInt() > 0)
  {
    return false;
  }

  return true;
}

int SayHiToEspMessage::GetEspTaskID()
{
  return EspTaskID;
}

String SayHiToEspMessage::GetGreeting()
{
  return Greeting;
}

std::list<String> SayHiToEspMessage::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(TaskID));
  printStrings.push_back(String(EspTask::SayHiToEsp));
  printStrings.push_back(String(EspTaskID));
  printStrings.push_back(Greeting);
  return printStrings;
}