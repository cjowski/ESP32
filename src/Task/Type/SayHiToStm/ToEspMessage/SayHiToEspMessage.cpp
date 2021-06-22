#include "SayHiToEspMessage.h"

SayHiToEspMessage::SayHiToEspMessage(UndefinedSerialTask serialTask)
{
  TaskID = serialTask.GetTaskID();
  std::list<String> otherSerialTexts = serialTask.GetOtherSerialTexts();
  auto it = otherSerialTexts.begin();
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

bool SayHiToEspMessage::SerialTaskMatched(UndefinedSerialTask serialTask)
{
  std::list<String> otherSerialTexts = serialTask.GetOtherSerialTexts();
  if (serialTask.GetTaskType() != EspTask::SayHiToEsp
    || otherSerialTexts.size() != OTHER_SERIAL_TEXTS_COUNT
  )
  {
    return false;
  }

  auto it = otherSerialTexts.begin();
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