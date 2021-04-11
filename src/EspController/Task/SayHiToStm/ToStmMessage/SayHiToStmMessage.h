#ifndef SAY_HI_TO_STM_MESSAGE_H
#define SAY_HI_TO_STM_MESSAGE_H

  #include "Task/EspTask.h"
  #include "Serial/Value/SerialValue.h"

  class SayHiToStmMessage : public SerialValue
  {
    private:
    int TaskID;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    SayHiToStmMessage(int taskID);
    int SERIAL_VALUES_COUNT() const { return 1; };
    char SERIAL_VALUE_KEY() const { return 'T'; };
    std::list<String> GetPrintStrings();
  };

#endif