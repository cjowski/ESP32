#ifndef ESP_SERVER_STORAGE_H
#define ESP_SERVER_STORAGE_H

  #include "Json/JsonContainer.h"
  #include "Json/FmChannelValues/FmChannelValues.h"
  #include "Json/GyroValues/GyroValues.h"
  #include "Json/Motors/Motors.h"
  #include "Json/SayHiStmResponse/SayHiStmResponse.h"
  
  class EspServerStorage
  {
    public:
    JsonContainer *FmChannelValuesContainer;
    JsonContainer *GyroValuesContainer;
    JsonContainer *MotorsContainer;

    EspServerStorage();
    void AddFmChannelValues(FmChannelValues *fmChannelValues);
    void AddGyroValues(GyroValues *gyroValues);
    void AddMotors(Motors *motors);
  };

#endif