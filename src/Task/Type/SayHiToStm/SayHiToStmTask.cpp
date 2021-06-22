#include "SayHiToStmTask.h"

SayHiToStmTask::SayHiToStmTask(
  int id,
  int startTime,
  SerialPrinter *printer,
  bool debugMode
)
{
  ID = id;
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = printer;
  DebugMode = debugMode;
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

  if (DebugMode)
  {
    Serial.println(
      "ESP taskID: " + String(ID) + ", ESP taskType: " + String(EspTask::SayHiToStm)
    );
  }

  Printer->Println(message->GetSerialEncoderInput());
  delete message;
}