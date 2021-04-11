#include "SayHiToStmTask.h"

SayHiToStmTask::SayHiToStmTask(int id, int startTime, SerialPrinter *serialPrinter)
{
  ID = id;
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = serialPrinter;
}

String SayHiToStmTask::GetStmGreeting()
{
  return StmGreeting;
}

bool SayHiToStmTask::ReceivedGreeting()
{
  return GreetingSet;
}

void SayHiToStmTask::SetStmGreeting(String stmGreeting)
{
  StmGreeting = stmGreeting;
  GreetingSet = true;
}

void SayHiToStmTask::Loop()
{
  SayHiToStmMessage *message = new SayHiToStmMessage(ID);
  Printer->Println(message);
  delete message;
}