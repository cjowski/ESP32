#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include "SerialReader\Read\String\SerialStringReader.h"
  #include "SerialReader\Value\SerialReadValueList.h"
  #include "EspServer\EspServer.h"
  #include "Json\GyroValues\GyroValues.h"
  #include "Json\FmChannelValues\FmChannelValues.h"
  #include "Json\SerialJsonContainer.h"

  #define SERIAL2_RX_PIN 16
  #define SERIAL2_TX_PIN 17
  #define SERIAL_BAUD_RATE 19200
  #define SERIAL_SIZE_RX 512

  #define ESP_SERVER_PORT 80

  #define SERIAL_READ_VALUE_LIST 50
  #define JSON_BUFFER_SIZE 10000

  class EspController
  {
    private:
    SerialReader *MySerialReader;
    EspServer *MyEspServer;
    SerialReadValueList *FmChannelValuesList;
    SerialReadValueList *GyroValuesList;

    void UpdateEspServerJson();
    bool SerialReaderHasFmChannelValues();
    bool SerialReaderHasGyroValues();

    public:
    EspController();
    void Setup(char *ssid, char *password);
    void Loop();
  };
  
#endif