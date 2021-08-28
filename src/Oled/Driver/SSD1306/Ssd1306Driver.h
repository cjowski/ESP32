#ifndef SSD_1306_DRIVER
#define SSD_1306_DRIVER

  #include <Adafruit_SSD1306.h>
  #include "Oled/Driver/OledDriver.h"

  class Ssd1306Driver : public OledDriver
  {
    private:
    Adafruit_SSD1306 *Oled;

    public:
    Ssd1306Driver(
      int screenWidth,
      int screenHeight
    );
    void Begin();
    void Display();
    void ClearDisplay();
    void SetFontSize(FontSize size);
    void SetFontColor(OledColor color);
    void SetCursorAtBeginning();
    void SetCursor(int x, int y);
    void Print(String text);
    void Println();
    void Println(String text);
  };

#endif