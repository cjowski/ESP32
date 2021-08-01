#include "OledController.h"

OledController::OledController(
  int screenWidth,
  int screenHeight,
  int displayDelay
)
{
  ScreenWidth = screenWidth;
  ScreenHeight = screenHeight;
  DisplayDelay = displayDelay;
  Oled = new Adafruit_SSD1306(screenWidth, screenHeight, &Wire, -1);
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
  Oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
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