#ifndef SAY_HI_TO_ESP_MESSAGE_H
#define SAY_HI_TO_ESP_MESSAGE_H

  #include "Task/EspTask.h"
  #include "Serial/Value/SerialValue.h"

  class SayHiToEspMessage : public SerialValue
  {
    private:
    int TaskID;
    String Greeting;
    int EspTaskID;
    static bool IsInteger(String text);

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    SayHiToEspMessage() { };
    SayHiToEspMessage(std::list<String> serialValues);
    int SERIAL_VALUES_COUNT() const { return 4; };
    char SERIAL_VALUE_KEY() const { return EspTask::SERIAL_VALUE_KEY; };
    int GetEspTaskID();
    String GetGreeting();
    std::list<String> GetPrintStrings();
  };

#endif