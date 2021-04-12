#include "ControllerApiRequestProcessor.h"

ControllerApiRequestProcessor::ControllerApiRequestProcessor(
  TaskController *taskController
)
{
  MyTaskController = taskController;
}

ControllerApiResponse *ControllerApiRequestProcessor::ProcessApiRequest(ControllerApiRequest *apiRequest)
{
  if (apiRequest->Key == ControllerApiRequest::SayHiToStm)
  {
    SayHiToStmTask *sayHiToStmTask = new SayHiToStmTask(
      MyTaskController->GetNewTaskID(),
      millis(),
      new SerialPrinter(&Serial2)
    );

    MyTaskController->AddTask(sayHiToStmTask);

    return new ControllerApiResponse(
      ControllerApiResponse::TaskInitialized,
      new TaskStatus(
        sayHiToStmTask->ID,
        sayHiToStmTask->Done
      )
    );
  }
  else if (apiRequest->Key == ControllerApiRequest::SayHiToStmStatus)
  {
    SayHiToStmTask *sayHiToStmTask = (SayHiToStmTask*)MyTaskController->GetTaskWithID(
      ((IntegerJson*)(apiRequest->JsonData))->GetValue()
    );
    if (sayHiToStmTask != nullptr)
    {
      return new ControllerApiResponse(
        ControllerApiResponse::SayHiStmResponse,
        new SayHiStmResponse(
          sayHiToStmTask->GetStmGreeting(),
          sayHiToStmTask->ReceivedGreeting()
        )
      );
    }
  }

  return new ControllerApiResponse(
    ControllerApiResponse::InvalidRequestKey,
    new EmptyJson()
  );
}