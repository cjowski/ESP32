#include "EspController.h"

EspController::EspController()
{
  FmChannelValuesList = new SerialReadValueList(SERIAL_READ_VALUE_LIST);
  GyroValuesList = new SerialReadValueList(SERIAL_READ_VALUE_LIST);
}

void EspController::Setup(char *ssid, char *password)
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  MySerialReader = new SerialStringReader(&Serial2);
  MyEspServer = new EspServer(ESP_SERVER_PORT, &Serial);
  MyEspServer->Connect(ssid, password); 
}

void EspController::Loop()
{
  MySerialReader->Read();
  UpdateEspServerJson();
}

void EspController::UpdateEspServerJson()
{
  if (SerialReaderHasFmChannelValues())
  {
    FmChannelValuesList->Add(MySerialReader->GetRecentReadValue()->GetCopy());
    MyEspServer->FmChannelValuesJson = SerialJsonContainer(
      "FmChannelValues",
      FmChannelValuesList->ToSerialJsonList<FmChannelValues>(),
      JSON_BUFFER_SIZE
    ).GetSerializedJson();
  }
  else if (SerialReaderHasGyroValues())
  {
    GyroValuesList->Add(MySerialReader->GetRecentReadValue()->GetCopy());
    MyEspServer->GyroValuesJson = SerialJsonContainer(
      "GyroValues",
      GyroValuesList->ToSerialJsonList<GyroValues>(),
      JSON_BUFFER_SIZE
    ).GetSerializedJson();
  }
}

bool EspController::SerialReaderHasFmChannelValues()
{
  return FmChannelValues::SERIAL_PRINT_KEY == MySerialReader->GetRecentReadValue()->GetSerialPrintKey()
    && FmChannelValues::SerialReadTextValid(
      MySerialReader->GetRecentReadValue()->ToString()
    );
}

bool EspController::SerialReaderHasGyroValues()
{
  return GyroValues::SERIAL_PRINT_KEY == MySerialReader->GetRecentReadValue()->GetSerialPrintKey()
    && GyroValues::SerialReadTextValid(
      MySerialReader->GetRecentReadValue()->ToString()
    );
}