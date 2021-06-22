#ifndef SAY_HI_TO_STM_TASK_H
#define SAY_HI_TO_STM_TASK_H

  #include <Serial/Print/SerialPrinter.h>
  #include "Task/EspTask.h"
  #include "ToStmMessage/SayHiToStmMessage.h"
  #include "ToEspMessage/SayHiToEspMessage.h"

  class SayHiToStmTask : public EspTask
  {
    private:
    SerialPrinter *Printer;
    String StmGreeting = "";
    bool GreetingSet = false;
    bool DebugMode = false;

    public:
    EspTaskType TYPE() const { return EspTaskType::SayHiToStm; };
    int LIFE_TIME() const { return 1200; };
    int LOOP_STEP_DELAY_TIME() const { return 250; };

    SayHiToStmTask(
      int id,
      int startTime,
      SerialPrinter *printer,
      bool debugMode
    );
    String GetStmGreeting();
    bool ReceivedGreeting();
    void SetStmGreeting(String stmGreeting);
    void Loop();
  };

#endif