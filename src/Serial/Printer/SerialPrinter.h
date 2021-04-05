#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H

  #include <HardwareSerial.h>
  #include "Serial/Value/SerialValue.h"

  class SerialPrinter
  {
    private:
    HardwareSerial *PrintSerial;
    
    public:
    SerialPrinter(HardwareSerial *printSerial);
    void Print(SerialValue *value);
    void Println(SerialValue *value);
  };

#endif