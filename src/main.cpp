#include <Arduino.h>
#include "SerialReader\String\SerialStringReader.h"
#include "SerialReader\SerialReadValueList.h"
#include "EspServer\EspServer.h"
#include "Json\FmChannelValues\FmChannelValues.h"
#include "Json\FmChannelValues\FmChannelValuesContainer.h"

#define SERIAL2_RX_PIN 16
#define SERIAL2_TX_PIN 17
#define SERIAL_BAUD_RATE 9600
#define SERIAL_SIZE_RX 512

#define ESP_SERVER_PORT 80

#define SERIAL_READ_VALUE_LIST 50
#define FM_CHANNEL_VALUES_JSON_BUFFER_SIZE 10000

const char* TEXT_CONTENT_TYPE = "application/json";
const char* SSID = "UPCCD6A9E8";
const char* PASSWORD = "tkr8QejnrMtr";

int currentTime = 0;
int lastTime = 0;

SerialReader *serialReader;
EspServer *espServer;
SerialReadValueList *readValuesList;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial2.begin(SERIAL_BAUD_RATE, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  serialReader = new SerialStringReader(&Serial2);
  espServer = new EspServer(ESP_SERVER_PORT, &Serial, TEXT_CONTENT_TYPE);
  espServer->Connect((char*)SSID, (char*)PASSWORD);
  readValuesList = new SerialReadValueList(SERIAL_READ_VALUE_LIST);
}

String getSingleFmChannelValues() {
  return FmChannelValues(
    serialReader->GetRecentReadValue()->GetText()
  ).GetSerializedJson();
}

String getMultipleFmChannelValues() {
  return FmChannelValuesContainer(
    readValuesList->GetStringList(),
    FM_CHANNEL_VALUES_JSON_BUFFER_SIZE
  ).GetSerializedJson();
}

void updateEspServerTextToSend()
{
  if (FmChannelValues::SerialReadTextValid(serialReader->GetRecentReadValue()->GetText()))
  {
    readValuesList->Add(serialReader->GetRecentReadValue()->GetCopy());

    espServer->SetTextToSend(
      //getSingleText()
      getMultipleFmChannelValues()
    );
  }
}

void loop() {
  //delay(10);
  serialReader->Read();
  updateEspServerTextToSend();
  //Serial.println(serialReader->GetRecentReadValue()->GetText());
}