#include "EspController.h"

EspController::EspController()
{
  FmChannelValuesList = new SerialReadValueList(SERIAL_READ_VALUE_LIST);
  GyroValuesList = new SerialReadValueList(SERIAL_READ_VALUE_LIST);
}

void EspController::Setup(char *ssid, char *password, Mode espMode)
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  MySerialReader = new SerialStringReader(&Serial2);
  MyEspServer = new EspServer(ESP_SERVER_PORT, &Serial);

  switch (espMode)
  {
    case Mode::accessPoint:
    {
      MyEspServer->SetAccessPoint(ssid, password);
      MyEspServer->SetupApi();
      break;
    }
    case Mode::wifi:
    {
      MyEspServer->ConnectToWifi(ssid, password);
      MyEspServer->SetupApi();
      break;
    }
    default: {
      break;
    }
  }
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
    MyEspServer->Storage.FmChannelValuesJson = SerialJsonContainer(
      "FmChannelValues",
      FmChannelValuesList->ToSerialJsonList<FmChannelValues>(),
      JSON_BUFFER_SIZE
    ).GetSerializedJson();
  }
  else if (SerialReaderHasGyroValues())
  {
    GyroValuesList->Add(MySerialReader->GetRecentReadValue()->GetCopy());
    MyEspServer->Storage.GyroValuesJson = SerialJsonContainer(
      "GyroValues",
      GyroValuesList->ToSerialJsonList<GyroValues>(),
      JSON_BUFFER_SIZE
    ).GetSerializedJson();
  }
}

bool EspController::SerialReaderHasFmChannelValues()
{
  FmChannelValues fmChannelValues = FmChannelValues();
  return fmChannelValues.SerialPrintKey() == MySerialReader->GetRecentReadValue()->GetSerialPrintKey()
    && fmChannelValues.SerialReadTextValid(
      MySerialReader->GetRecentReadValue()->ToString()
    );
}

bool EspController::SerialReaderHasGyroValues()
{
  GyroValues gyroValues = GyroValues();
  return gyroValues.SerialPrintKey() == MySerialReader->GetRecentReadValue()->GetSerialPrintKey()
    && gyroValues.SerialReadTextValid(
      MySerialReader->GetRecentReadValue()->ToString()
    );
}