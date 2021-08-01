#ifndef IP_DISPLAYER_H
#define IP_DISPLAYER_H

  #include <functional>
  #include "Oled/OledController.h"

  class IpDisplayer : public OledController
  {
    private:
    std::function<String(void)> GetAccessPointIp;
    std::function<String(void)> GetWifiIp;

    protected:
    void Display();

    public:
    IpDisplayer(
      int screenWidth,
      int screenHeight,
      int displayDelay,
      std::function<String(void)> getAccessPointIp,
      std::function<String(void)> getWifiIp
    );
  };

#endif