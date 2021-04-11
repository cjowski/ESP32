#ifndef ESP_TASK_H
#define ESP_TASK_H

  class EspTask
  {
    public:
    enum EspTaskType
    {
      SayHiToStm
    };
    enum StmTaskType
    {
      SayHiToEsp
    };

    EspTask() { };
    EspTask(int id);
    virtual ~EspTask() { };
    int ID = -1;
    bool Done = false;
    int StartTime = 0;
    int PreviousStepTime = 0;
    static const char SERIAL_VALUE_KEY = 'T';

    virtual EspTaskType TYPE() const = 0;
    virtual int LIFE_TIME() const = 0;
    virtual int LOOP_STEP_DELAY_TIME() const = 0;
    virtual void Loop() = 0;
    bool IsReadyForLoop(int currentTime);
    bool IsOvertime(int currentTime);
  };

#endif