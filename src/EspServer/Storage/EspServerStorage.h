#ifndef ESP_SERVER_STORAGE_H
#define ESP_SERVER_STORAGE_H

  #include "Json/JsonContainer.h"
  #include "Json/Serial/FmChannelValues/FmChannelValues.h"
  #include "Json/Serial/GyroValues/GyroValues.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"
  
  class EspServerStorage
  {
    public:
    JsonContainer *FmChannelValuesContainer;
    JsonContainer *GyroValuesContainer;

    EspServerStorage();
    void AddFmChannelValues(FmChannelValues *fmChannelValues);
    void AddGyroValues(GyroValues *gyroValues);
  };

#endif