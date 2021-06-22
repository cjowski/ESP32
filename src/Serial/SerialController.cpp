#include "SerialController.h"

SerialController::SerialController(
  SerialReader *reader,
  TaskController *taskController,
  EspServerStorage *storage
)
{
  Reader = reader;
  MyTaskController = taskController;
  Storage = storage;
}

void SerialController::Loop()
{
  SerialDecoderOutput *decoderOutput = Reader->Read();
  ProcessDecoderOutput(decoderOutput);
  delete decoderOutput;
}

void SerialController::ProcessDecoderOutput(SerialDecoderOutput *decoderOutput)
{
  if (!decoderOutput->Exists)
  {
    return;
  }

  if (FmChannelValues::SerialDecoderOutputMatched(decoderOutput))
  {
    Storage->AddFmChannelValues(
      new FmChannelValues(decoderOutput)
    );
  }
  else if (GyroValues::SerialDecoderOutputMatched(decoderOutput))
  {
    Storage->AddGyroValues(
      new GyroValues(decoderOutput)
    );
  }
  else if (Motors::SerialDecoderOutputMatched(decoderOutput))
  {
    Storage->AddMotors(
      new Motors(decoderOutput)
    );
  }
  else if (UndefinedSerialTask::SerialDecoderOutputMatched(decoderOutput))
  {
    MyTaskController->ProcessUndefinedSerialTask(
      UndefinedSerialTask(decoderOutput)
    );
  }
}