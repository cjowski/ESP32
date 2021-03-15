#ifndef ESP_SERVER_STORAGE_H
#define ESP_SERVER_STORAGE_H

  #include <WString.h>
  
  struct EspServerStorage
  {
    public:
    String FmChannelValuesJson = "null";
    String GyroValuesJson = "null";
  };

#endif