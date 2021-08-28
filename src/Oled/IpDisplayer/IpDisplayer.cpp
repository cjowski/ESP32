#include "IpDisplayer.h"

IpDisplayer::IpDisplayer(
  OledDriver *driver,
  int displayDelay,
  std::function<String(void)> getAccessPointIp,
  std::function<String(void)> getWifiIp,
  std::function<String(void)> getWebSocketClientIp
) : OledController(driver, displayDelay)
{
  GetAccessPointIp = getAccessPointIp;
  GetWifiIp = getWifiIp;
  GetWebSocketClientIp = getWebSocketClientIp;
}

void IpDisplayer::Display()
{
  Driver->ClearDisplay();

  Driver->SetFontSize(FontSize::Small);
  Driver->SetFontColor(OledColor::White);
  Driver->SetCursorAtBeginning();
  Driver->Print("AP:   ");
  Driver->Println(GetAccessPointIp());
  Driver->Print("WiFi: ");
  Driver->Print(GetWifiIp());
  Driver->Println();
  Driver->Println();
  Driver->Println("WebSocket client: ");

  String webSocketClientIp = GetWebSocketClientIp();
  if (!webSocketClientIp.isEmpty())
  {
    Driver->Print(webSocketClientIp);
  }
  else
  {
    Driver->Print("none");
  }

  Driver->Display();
}