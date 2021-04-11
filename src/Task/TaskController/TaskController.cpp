#include "TaskController.h"

TaskController::TaskController() { }

int TaskController::GetNewTaskID()
{
  return NextTaskID++;
}

void TaskController::AddTask(EspTask *newTask)
{
  Tasks.push_back(newTask);
}

void TaskController::AddProcessedStmTaskID(int stmTaskID)
{
  ProcessedStmTaskIDs.push_back(stmTaskID);
}

bool TaskController::StmTaskProcessed(int stmTaskID)
{
  return std::find(
    ProcessedStmTaskIDs.begin(),
    ProcessedStmTaskIDs.end(),
    stmTaskID
  ) != ProcessedStmTaskIDs.end();
}

EspTask* TaskController::GetTaskWithID(int espTaskID)
{
  EspTask* foundTask = nullptr;
  for (auto it = Tasks.begin(); it != Tasks.end(); it++)
  {
    if ((*it)->ID == espTaskID)
    {
      foundTask = *it;
      break;
    }
  }
  return foundTask;
}

void TaskController::Loop()
{
  int currentTime = millis();
  KillDoneOrOvertimeTasks(currentTime);
  for (auto it = Tasks.begin(); it != Tasks.end(); it++)
  {
    if ((*it)->IsReadyForLoop(currentTime))
    {
      (*it)->Loop();
      (*it)->PreviousStepTime = currentTime;
    }
  }
}

void TaskController::KillDoneOrOvertimeTasks(int currentTime)
{
  int currentTaskIndex = 0;
  std::list<int> deadTaskIndexes;
  for (auto it = Tasks.begin(); it != Tasks.end(); it++, currentTaskIndex++)
  {
    if ((*it)->Done || (*it)->IsOvertime(currentTime))
    {
      delete *it;
      deadTaskIndexes.push_back(currentTaskIndex);
    }
  }

  std::list<EspTask*>::iterator taskIterator;
  for (auto it = deadTaskIndexes.begin(); it != deadTaskIndexes.end(); it++)
  {
    taskIterator = Tasks.begin();
    advance(taskIterator, *it);
    Tasks.erase(taskIterator);
  }
}