#ifndef OLED_DRIVER
#define OLED_DRIVER

  #include <WString.h>
  #include "FontSize.h"
  #include "OledColor.h"

  class OledDriver
  {
    public:
    virtual void Begin() = 0;
    virtual void Display() = 0;
    virtual void ClearDisplay() = 0;
    virtual void SetFontSize(FontSize size) = 0;
    virtual void SetFontColor(OledColor color) = 0;
    virtual void SetCursorAtBeginning() = 0;
    virtual void SetCursor(int x, int y) = 0;
    virtual void Print(String text) = 0;
    virtual void Println() = 0;
    virtual void Println(String text) = 0;
  };

#endif