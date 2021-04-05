#include "SayHiToStmTask.h"

SayHiToStmTask::SayHiToStmTask(int id, int startTime, SerialPrinter *serialPrinter)
{
  ID = id;
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = serialPrinter;
}

void SayHiToStmTask::Loop()
{
  SayHiToStmMessage *message = new SayHiToStmMessage(5);
  Printer->Println(message);
  delete message;
}