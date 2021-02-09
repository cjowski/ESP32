#include "SerialReadValueList.h"

SerialReadValueList::SerialReadValueList(int maxListSize)
{
  MaxListSize = maxListSize;
}

void SerialReadValueList::Add(SerialReadValue newValue)
{
  if (!Values.back().Equals(newValue))
  {
    if (Values.size() == MaxListSize)
    {
      Values.pop_front();
    }

    Values.push_back(newValue);
  }
}

std::list<String> SerialReadValueList::ToStringList()
{
  std::list<String> outputList;

  std::list<SerialReadValue>::iterator it;
  for (it = Values.begin(); it != Values.end(); it++)
  {
    outputList.push_back(it->ToString());
  }

  return outputList;
}

String SerialReadValueList::ToString()
{
  String outputString = "";

  std::list<SerialReadValue>::iterator it;
  for (it = Values.begin(); it != Values.end(); it++)
  {
    outputString += it->ToString() + "\n";
  }

  return outputString;
}