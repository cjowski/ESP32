#ifndef TASK_STATUS_H
#define TASK_STATUS_H

  #include "Json/Json.h"

  class TaskStatus : public Json
  {
    private:
    int TaskID;
    bool Done;

    public:
    int JSON_BUFFER_SIZE() const { return 50; };
    TaskStatus(int taskID, bool done);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson) { return false; }
  };

#endif