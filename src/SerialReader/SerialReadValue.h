#ifndef SERIAL_READ_VALUE_H
#define SERIAL_READ_VALUE_H

  #include <WString.h>

  class SerialReadValue
  {
    private:
    String TextValue;

    public:
    SerialReadValue();
    bool Equals(SerialReadValue valueToCompare);
    void SetNewTextValue(String textValue);
    SerialReadValue GetCopy();
    String GetText();
  };

#endif