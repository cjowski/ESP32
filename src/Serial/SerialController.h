#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include <Serial/Read/SerialReader.h>
  #include <Serial/Type/StringList/Decoder/StringListDecoder.h>
  #include "EspServer/Storage/EspServerStorage.h"
  #include "Task/TaskController/TaskController.h"
  #include "Json/FmChannelValues/FmChannelValues.h"
  #include "Json/GyroValues/GyroValues.h"
  #include "Json/Motors/Motors.h"

  #define SERIAL2_RX_PIN 16
  #define SERIAL2_TX_PIN 17
  #define SERIAL_BAUD_RATE 19200
  #define SERIAL_SIZE_RX 512

  class SerialController
  {
    private:
    SerialReader *Reader;
    TaskController *MyTaskController;
    EspServerStorage *Storage;

    void ProcessDecoderOutput(SerialDecoderOutput *decoderOutput);

    public:
    SerialController(
      SerialReader *reader,
      TaskController *taskController,
      EspServerStorage *storage
    );
    void Loop();
  };

#endif