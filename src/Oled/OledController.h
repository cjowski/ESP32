#ifndef OLED_CONTROLLER_H
#define OLED_CONTROLLER_H

  #include <Adafruit_GFX.h>
  #include <Adafruit_I2CDevice.h>
  #include "Driver/OledDriver.h"

  class OledController
  {
    private:
    const int CHECK_DEVICE_DELAY = 1000;

    int ScreenWidth;
    int ScreenHeight;
    int DisplayDelay;
    bool CanDisplay = false;
    unsigned long PreviousDeviceCheckTime = 0;
    unsigned long PreviousDeviceDisplayTime = 0;

    bool IsDeviceConnected();
    void StartDisplaying();
    void EndDisplaying();

    protected:
    OledDriver *Driver;
    virtual void Display() = 0;

    public:
    OledController() { };
    OledController(
      OledDriver *driver,
      int displayDelay
    );
    virtual ~OledController() { };
    void Loop();
  };

#endif