#include <rtc/rtc.hpp>

int main()
{
  rtc::Configuration config;
  config.disableAutoNegotiation = true;

  const auto pc = std::make_shared<rtc::PeerConnection>(config);
}
