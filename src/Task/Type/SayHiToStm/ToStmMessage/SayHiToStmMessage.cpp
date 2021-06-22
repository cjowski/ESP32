#include "SayHiToStmMessage.h"

SayHiToStmMessage::SayHiToStmMessage(int taskID)
{
  TaskID = taskID;
}

SerialEncoderInput *SayHiToStmMessage::GetSerialEncoderInput()
{
  std::list<String> texts;
  texts.push_back(String(TaskID));
  texts.push_back(String(EspTask::SayHiToStm));

  return new StringListEncoderInput(
    SERIAL_KEY,
    texts
  );
}