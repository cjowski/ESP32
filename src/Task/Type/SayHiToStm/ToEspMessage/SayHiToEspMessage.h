#ifndef SAY_HI_TO_ESP_MESSAGE_H
#define SAY_HI_TO_ESP_MESSAGE_H

  #include "Task/EspTask.h"
  #include "Task/UndefinedSerialTask.h"

  class SayHiToEspMessage
  {
    private:
    static const int OTHER_SERIAL_TEXTS_COUNT = 2;

    int TaskID;
    String Greeting;
    int EspTaskID;
    static bool IsInteger(String text);

    public:
    SayHiToEspMessage() { };
    SayHiToEspMessage(UndefinedSerialTask serialTask);
    int GetEspTaskID();
    String GetGreeting();
    static bool SerialTaskMatched(UndefinedSerialTask serialTask);
  };

#endif