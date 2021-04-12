#include "SerialController.h"

SerialController::SerialController(
  TaskController *taskController,
  EspServerStorage *storage
)
{
  MyTaskController = taskController;
  Storage = storage;
  Serial.begin(SERIAL_BAUD_RATE);
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  MySerialReader = new SerialReader(&Serial2);
}

void SerialController::Loop()
{
  ProcessSerialValue(
    MySerialReader->Read()
  );
}

void SerialController::ProcessSerialValue(UndefinedSerialValue serialValue)
{
  if (!serialValue.Exists())
  {
    return;
  }

  char readValueKey = serialValue.GetReadValueKey();
  std::list<String> serialValues = serialValue.GetPrintStrings();
  if (UndefinedSerialTask().SerialValueValid(readValueKey, serialValues))
  {
    ProcessSerialValueTask(
      UndefinedSerialTask(serialValue)
    );
    return;
  }
  else if (FmChannelValues().SerialValueValid(readValueKey, serialValues))
  {
    Storage->AddFmChannelValues(
      new FmChannelValues(serialValues)
    );
  }
  else if (GyroValues().SerialValueValid(readValueKey, serialValues))
  {
    Storage->AddGyroValues(
      new GyroValues(serialValues)
    );
  }
}

void SerialController::ProcessSerialValueTask(UndefinedSerialTask serialTask)
{
  if (!MyTaskController->StmTaskProcessed(serialTask.GetTaskID()))
  {
    UndefinedSerialValue serialValue = serialTask.GetSerialValue();
    char readValueKey = serialValue.GetReadValueKey();
    std::list<String> serialValues = serialValue.GetPrintStrings();
    if (SayHiToEspMessage().SerialValueValid(readValueKey, serialValues))
    {
      SayHiToEspMessage sayHiToEspMessage = SayHiToEspMessage(serialValues);
      SayHiToStmTask *sayHiToStmTask = (SayHiToStmTask*)MyTaskController->GetTaskWithID(
        sayHiToEspMessage.GetEspTaskID()
      );
      if (sayHiToStmTask != nullptr)
      {
        sayHiToStmTask->SetStmGreeting(
          sayHiToEspMessage.GetGreeting()
        );
        Serial.println(sayHiToEspMessage.GetGreeting());
        MyTaskController->AddProcessedStmTaskID(serialTask.GetTaskID());
      }
    }
  }
}