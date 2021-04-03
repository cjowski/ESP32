#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H

  #include <HardwareSerial.h>
  #include "Serial/Printer/Value/SerialPrintValue.h"

  class SerialPrinter
  {
    public:
    SerialPrinter(HardwareSerial *printSerial, int serialBaudRate);
    void Print(SerialPrintValue value);
    void Println(SerialPrintValue value);

    private:
    HardwareSerial *PrintSerial;
    int SerialBaudRate;
  };

#endif