#ifndef ESP_CONTROLLER_H
#define ESP_CONTROLLER_H

  #include "SerialReader/Read/String/SerialStringReader.h"
  #include "SerialReader/ValueInterpreter/SerialValueInterpreter.h"
  #include "EspServer/EspServer.h"

  #define SERIAL2_RX_PIN 16
  #define SERIAL2_TX_PIN 17
  #define SERIAL_BAUD_RATE 19200
  #define SERIAL_SIZE_RX 512

  #define ESP_SERVER_PORT 80

  class EspController
  {
    private:
    SerialReader *MySerialReader;
    EspServer *MyEspServer;

    void SetupSerials();
    void SetupServer(char *ssid, char *password, EspServer::Mode espMode);
    void AddSerialValueToStorage(
      SerialValueInterpreter::SerialValueType serialValueType,
      String serialValue
    );

    public:
    EspController();
    void Setup(char *ssid, char *password, EspServer::Mode espMode);
    void Loop();
  };
  
#endif