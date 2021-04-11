#ifndef UNDEFINED_SERIAL_TASK_H
#define UNDEFINED_SERIAL_TASK_H

  #include "Task/EspTask.h"
  #include "Serial/Value/UndefinedSerialValue.h"

  class UndefinedSerialTask : public SerialValue
  {
    private:
    int TaskID;
    int TaskType;
    std::list<String> OtherSerialValues;
    UndefinedSerialValue SerialValue;
    static bool IsInteger(String text);
    const unsigned int MIN_SERIAL_VALUE_COUNT = 2;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    UndefinedSerialTask() { };
    UndefinedSerialTask(UndefinedSerialValue serialValue);
    int SERIAL_VALUES_COUNT() const { return -1; };
    char SERIAL_VALUE_KEY() const { return EspTask::SERIAL_VALUE_KEY; };
    int GetTaskID();
    int GetTaskType();
    UndefinedSerialValue GetSerialValue();
    std::list<String> GetOtherSerialValues();
    std::list<String> GetPrintStrings();
  };

#endif