#include "OledController.h"

OledController::OledController(
  OledDriver *driver,
  int displayDelay
)
{
  Driver = driver;
  DisplayDelay = displayDelay;
}

bool OledController::IsDeviceConnected()
{
  Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      return true;
    }
  }
  return false;
}

void OledController::StartDisplaying()
{
  Driver->Begin();
  CanDisplay = true;
}

void OledController::EndDisplaying()
{
  CanDisplay = false;
}

void OledController::Loop()
{
  unsigned long currentTime = millis();

  if (currentTime - PreviousDeviceCheckTime > CHECK_DEVICE_DELAY)
  {
    if (!IsDeviceConnected()) {
      EndDisplaying();
    }
    else if (!CanDisplay)
    {
      StartDisplaying();
    }
    PreviousDeviceCheckTime = currentTime;
  }

  if (CanDisplay && currentTime - PreviousDeviceDisplayTime > DisplayDelay)
  {
    Display();
    PreviousDeviceDisplayTime = currentTime;
  }
}