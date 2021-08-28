#ifndef SH_1106_DRIVER
#define SH_1106_DRIVER

  #include <U8g2lib.h>
  #include "Oled/Driver/OledDriver.h"

  class Sh1106Driver : public OledDriver
  {
    private:
    U8G2 *Oled;
    int CursorX = 0;
    int CursorY = 0;
    int FontHeight = 0;
    int FontWidth = 0;

    public:
    Sh1106Driver(
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