#ifndef ESP_TASK_H
#define ESP_TASK_H

  class EspTask
  {
    public:
    EspTask() { };
    virtual ~EspTask() { };
    bool Done = false;
    int StartTime = 0;
    int PreviousStepTime = 0;

    virtual int LIFE_TIME() const = 0;
    virtual int LOOP_STEP_DELAY_TIME() const = 0;
    virtual void Loop() = 0;
    bool IsReadyForLoop(int currentTime);
    bool IsOvertime(int currentTime);
  };

#endif