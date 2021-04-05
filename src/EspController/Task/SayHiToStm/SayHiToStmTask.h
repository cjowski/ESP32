#ifndef SAY_HI_TO_STM_TASK_H
#define SAY_HI_TO_STM_TASK_H

  #include "Task/EspTask.h"
  #include "Serial/Printer/SerialPrinter.h"
  #include "Json/Serial/SayHiToStmMessage/SayHiToStmMessage.h"

  class SayHiToStmTask : public EspTask
  {
    private:
    SerialPrinter *Printer;

    public:
    EspTaskType TYPE() const { return EspTaskType::SayHiToStm; };
    int LIFE_TIME() const { return 5000; };
    int LOOP_STEP_DELAY_TIME() const { return 100; };

    SayHiToStmTask(int id, int startTime, SerialPrinter *serialPrinter);
    void Loop();
  };

#endif