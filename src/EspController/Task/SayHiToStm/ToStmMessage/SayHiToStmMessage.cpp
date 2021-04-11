#include "SayHiToStmMessage.h"

SayHiToStmMessage::SayHiToStmMessage(int taskID)
{
  TaskID = taskID;
}

std::list<String> SayHiToStmMessage::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(TaskID));
  printStrings.push_back(String(EspTask::SayHiToStm));
  return printStrings;
}