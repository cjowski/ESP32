#ifndef SAY_HI_TO_STM_TASK_H
#define SAY_HI_TO_STM_TASK_H

  #include "Task/EspTask.h"
  #include "Serial/Printer/SerialPrinter.h"

  class SayHiToStmTask : public EspTask
  {
    private:
    SerialPrinter *Printer;

    public:
    int LIFE_TIME() const { return 5000; };
    int LOOP_STEP_DELAY_TIME() const { return 100; };

    SayHiToStmTask(int startTime, SerialPrinter *serialPrinter);
    void Loop();
  };

#endif