#include "SerialPrinter.h"

SerialPrinter::SerialPrinter(HardwareSerial *printSerial)
{
  PrintSerial = printSerial;
}

void SerialPrinter::Print(SerialValue *value)
{
  PrintSerial->print(value->ToSerialString());
}

void SerialPrinter::Println(SerialValue *value)
{
  PrintSerial->println(value->ToSerialString());
}