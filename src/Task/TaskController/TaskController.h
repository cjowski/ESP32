#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

  #include <list>
  #include <esp32-hal-timer.h>
  #include "Task/EspTask.h"

  class TaskController
  {
    private:
    std::list<EspTask*> Tasks;
    void KillDoneOrOvertimeTasks(int currentTime);

    public:
    TaskController();
    void AddTask(EspTask *newTask);
    void Loop();
  };

#endif