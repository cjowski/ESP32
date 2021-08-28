#include "Sh1106Driver.h"

Sh1106Driver::Sh1106Driver(
  int screenWidth,
  int screenHeight
)
{
  if (screenWidth == 128 && screenHeight == 64)
  {
    Oled = new U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0);
  }
  else
  {
    Oled = new U8G2();
  }
}

void Sh1106Driver::Begin()
{
  Oled->begin();
}

void Sh1106Driver::Display()
{
  Oled->sendBuffer();
}

void Sh1106Driver::ClearDisplay()
{
  Oled->clearBuffer();
}

void Sh1106Driver::SetFontSize(FontSize size)
{
  switch(size)
  {
    case FontSize::Small:
      Oled->setFont(u8g2_font_profont12_mf);
      FontHeight = 12;
      FontWidth = 6;
      break;
    case FontSize::Medium:
      Oled->setFont(u8g2_font_profont15_mf);
      FontHeight = 15;
      FontWidth = 7;
      break;
    case FontSize::Large:
      Oled->setFont(u8g2_font_profont22_mf);
      FontHeight = 22;
      FontWidth = 11;
      break;
  }
}

void Sh1106Driver::SetFontColor(OledColor color)
{
  switch(color)
  {
    case OledColor::Black:
      Oled->setDrawColor(0);
      break;
    case OledColor::White:
      Oled->setDrawColor(1);
      break;
  }
}

void Sh1106Driver::SetCursorAtBeginning()
{
  CursorX = 0;
  CursorY = FontHeight;
}

void Sh1106Driver::SetCursor(int x, int y)
{
  CursorX = x;
  CursorY = y;
}

void Sh1106Driver::Print(String text)
{
  Oled->drawStr(CursorX, CursorY, text.c_str());
  CursorX += text.length() * FontWidth;
}

void Sh1106Driver::Println()
{
  CursorX = 0;
  CursorY += FontHeight;
}

void Sh1106Driver::Println(String text)
{
  Oled->drawStr(CursorX, CursorY, text.c_str());
  CursorX = 0;
  CursorY += FontHeight;
}