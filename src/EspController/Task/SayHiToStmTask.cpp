#include "SayHiToStmTask.h"

SayHiToStmTask::SayHiToStmTask(int startTime, SerialPrinter *serialPrinter)
{
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = serialPrinter;
}

void SayHiToStmTask::Loop()
{
  Printer->Println(SerialPrintValue(5));
}