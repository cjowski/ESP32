#ifndef SERIAL_READ_VALUE_H
#define SERIAL_READ_VALUE_H

  #include <WString.h>

  class SerialReadValue
  {
    private:
    char SerialPrintKey;
    String TextValue;

    public:
    SerialReadValue();
    bool Equals(SerialReadValue valueToCompare);
    void SetNewTextValue(char serialPrintKey, String textValue);
    SerialReadValue GetCopy();
    char GetSerialPrintKey();
    String ToString();
  };

#endif