#include "EspServerStorage.h"

EspServerStorage::EspServerStorage()
{
  FmChannelValuesContainer = new JsonContainer("FmChannelValues", 50, 10000);
  GyroValuesContainer = new JsonContainer("GyroValues", 50, 10000);
}

void EspServerStorage::AddSerialValue(
  SerialValueInterpreter::SerialValueType serialValueType,
  String serialValue
)
{
  switch(serialValueType)
  {
    case SerialValueInterpreter::FmChannelValuesJson:
      FmChannelValuesContainer->AddToContainer(
        new FmChannelValues(serialValue)
      );
      break;
    case SerialValueInterpreter::GyroValuesJson:
      GyroValuesContainer->AddToContainer(
        new GyroValues(serialValue)
      );
      break;
    default:
      break;
  }
}