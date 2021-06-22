#ifndef SAY_HI_TO_STM_MESSAGE_H
#define SAY_HI_TO_STM_MESSAGE_H

  #include <Serial/Type/StringList/Encoder/StringListEncoderInput.h>
  #include "Task/EspTask.h"

  class SayHiToStmMessage
  {
    private:
    static const char SERIAL_KEY = 'T';

    int TaskID;

    public:
    SayHiToStmMessage(int taskID);
    SerialEncoderInput *GetSerialEncoderInput();
  };

#endif