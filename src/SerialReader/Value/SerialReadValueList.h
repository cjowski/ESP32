#ifndef SERIAL_READ_VALUE_LIST_H
#define SERIAL_READ_VALUE_LIST_H

  #include "SerialReadValue.h"
  #include "Json/SerialJson.h"
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
    std::list<String> ToStringList();
    String ToString();

    template<class TSerialJsonClass>
    std::list<SerialJson*> ToSerialJsonList()
    {
      std::list<SerialJson*> outputList;

      std::list<SerialReadValue>::iterator it;
      for (it = Values.begin(); it != Values.end(); it++)
      {
        outputList.push_back(
          new TSerialJsonClass(it->ToString())
        );
      }

      return outputList;
    }
  };

#endif