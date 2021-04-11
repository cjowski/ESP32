#include "TaskStatus.h"

TaskStatus::TaskStatus(int taskID, bool done)
{
  TaskID = taskID;
  Done = done;
}

DynamicJsonDocument TaskStatus::GetJson()
{
  DynamicJsonDocument outputJson(JSON_BUFFER_SIZE());
  outputJson["TaskID"] = TaskID;
  outputJson["Done"] = Done;
  return outputJson;
}