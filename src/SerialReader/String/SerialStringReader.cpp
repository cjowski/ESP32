#include "SerialStringReader.h"

void SerialStringReader::Read()
{
  bool recvInProgress = false;
  bool newValueReady = false;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  String receivedTextInProgress = "";

  while (ReadSerial->available() > 0 && newValueReady == false) {
    rc = ReadSerial->read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedTextInProgress += rc;
      }
      else {
        recvInProgress = false;
        newValueReady = true;
        RecentReadValue->SetNewTextValue(receivedTextInProgress);
      }
    }
    else if (rc == startMarker) {
        recvInProgress = true;
    }
  }
}