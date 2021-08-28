#include "Ssd1306Driver.h"

Ssd1306Driver::Ssd1306Driver(
  int screenWidth,
  int screenHeight
)
{
  Oled = new Adafruit_SSD1306(screenWidth, screenHeight, &Wire, -1);
}

void Ssd1306Driver::Begin()
{
  Oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void Ssd1306Driver::Display()
{
  Oled->display();
}

void Ssd1306Driver::ClearDisplay()
{
  Oled->clearDisplay();
}

void Ssd1306Driver::SetFontSize(FontSize size)
{
  switch(size)
  {
    case FontSize::Small:
      Oled->setTextSize(1);
      break;
    case FontSize::Medium:
      Oled->setTextSize(2);
      break;
    case FontSize::Large:
      Oled->setTextSize(3);
      break;
  }
}

void Ssd1306Driver::SetFontColor(OledColor color)
{
  switch(color)
  {
    case OledColor::Black:
      Oled->setTextColor(BLACK);
      break;
    case OledColor::White:
      Oled->setTextColor(WHITE);
      break;
  }
}

void Ssd1306Driver::SetCursorAtBeginning()
{
  Oled->setCursor(0, 0);
}

void Ssd1306Driver::SetCursor(int x, int y)
{
  Oled->setCursor(x, y);
}

void Ssd1306Driver::Print(String text)
{
  Oled->print(text);
}

void Ssd1306Driver::Println()
{
  Oled->println();
}

void Ssd1306Driver::Println(String text)
{
  Oled->println(text);
}