#ifndef SERIAL_READ_VALUE_LIST_H
#define SERIAL_READ_VALUE_LIST_H

  #include "SerialReadValue.h"
  #include <list>
  #include <WString.h>

  class SerialReadValueList
  {
    private:
    int MaxListSize;
    std::list<SerialReadValue> Values;

    public:
    SerialReadValueList(int maxListSize);
    void Add(SerialReadValue newValue);
    std::list<String> GetStringList();
    String ToString();
  };

#endif