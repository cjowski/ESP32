#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

  #include <list>
  #include <algorithm>
  #include <esp32-hal-timer.h>
  #include "Task/EspTask.h"

  class TaskController
  {
    private:
    std::list<EspTask*> Tasks;
    void KillDoneOrOvertimeTasks(int currentTime);
    std::list<int> ProcessedStmTaskIDs;
    int NextTaskID = 1;

    public:
    TaskController();
    int GetNewTaskID();
    void AddTask(EspTask *newTask);
    void AddProcessedStmTaskID(int stmTaskID);
    bool StmTaskProcessed(int stmTaskID);
    EspTask *GetTaskWithID(int espTaskID);
    void Loop();
  };

#endif