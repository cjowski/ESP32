#ifndef OLED_CONTROLLER_H
#define OLED_CONTROLLER_H

  #include <Adafruit_SSD1306.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_I2CDevice.h>

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
    Adafruit_SSD1306 *Oled;
    virtual void Display() = 0;

    public:
    OledController() { };
    OledController(
      int screenWidth,
      int screenHeight,
      int displayDelay
    );
    virtual ~OledController() { };
    void Loop();
  };

#endif