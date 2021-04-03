#ifndef ESP_SERVER_STORAGE_H
#define ESP_SERVER_STORAGE_H

  #include <WString.h>
  #include "Serial/Reader/ValueInterpreter/SerialValueInterpreter.h"
  #include "Json/JsonContainer.h"
  #include "Json/Serial/FmChannelValues/FmChannelValues.h"
  #include "Json/Serial/GyroValues/GyroValues.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"
  
  class EspServerStorage
  {
    public:
    JsonContainer *FmChannelValuesContainer;
    JsonContainer *GyroValuesContainer;
    SayHiStmResponse *SayHeyStmResponse;

    EspServerStorage();
    void AddSerialValue(
      SerialValueInterpreter::SerialValueType serialValueType,
      String serialValue
    );
  };

#endif