#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

  #include <list>
  #include <algorithm>
  #include <esp32-hal-timer.h>
  #include "Task/EspTask.h"
  #include "Task/Type/SayHiToStm/SayHiToStmTask.h"
  #include "Task/Type/SayHiToStm/ToEspMessage/SayHiToEspMessage.h"

  class TaskController
  {
    private:
    std::list<EspTask*> Tasks;
    SerialPrinter *Printer;
    void KillDoneOrOvertimeTasks(int currentTime);
    std::list<int> ProcessedStmTaskIDs;
    int NextTaskID = 1;
    bool DebugMode = false;

    public:
    TaskController(SerialPrinter *printer, bool debugMode);
    int GetNewTaskID();
    void AddTask(EspTask *newTask);
    void AddProcessedStmTaskID(int stmTaskID);
    bool StmTaskProcessed(int stmTaskID);
    EspTask *GetTaskWithID(int espTaskID);
    SerialPrinter *GetPrinter();
    void ProcessUndefinedSerialTask(UndefinedSerialTask undefinedSerialTask);
    void Loop();
  };

#endif