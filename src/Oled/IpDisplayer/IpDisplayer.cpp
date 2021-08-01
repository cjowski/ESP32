#include "IpDisplayer.h"

IpDisplayer::IpDisplayer(
  int screenWidth,
  int screenHeight,
  int displayDelay,
  std::function<String(void)> getAccessPointIp,
  std::function<String(void)> getWifiIp
) : OledController(screenWidth, screenHeight, displayDelay)
{
  GetAccessPointIp = getAccessPointIp;
  GetWifiIp = getWifiIp;
}

void IpDisplayer::Display()
{
  Oled->clearDisplay();

  Oled->setTextSize(1);
  Oled->setTextColor(WHITE);
  Oled->setCursor(0, 0);
  Oled->print("AP:   ");
  Oled->println(GetAccessPointIp());
  Oled->print("WiFi: ");
  Oled->print(GetWifiIp());

  Oled->display();
}