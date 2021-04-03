#include "SerialPrinter.h"

SerialPrinter::SerialPrinter(HardwareSerial *printSerial, int serialBaudRate)
{
  PrintSerial = printSerial;
  SerialBaudRate = serialBaudRate;
}

void SerialPrinter::Print(SerialPrintValue value)
{
  PrintSerial->print(value.GetValue());
}

void SerialPrinter::Println(SerialPrintValue value)
{
  PrintSerial->println(value.GetValue());
}