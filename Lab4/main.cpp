#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>
#include "gpioaregisters.hpp"
int main()
{
RCC::CR::HSEON::On::Set();
while(!RCC::CR::HSERDY::Ready::IsSet())
{
}
RCC::CFGR::SW::Hse::Set();
while(!RCC::CFGR::SWS::Hse::IsSet())
{
}
RCC::PLLCFGR::PLLM0::Set(4U); //Set VCO 2MHz==HSE/4==8 MHz/4
RCC::PLLCFGR::PLLN0::Set(50U); //Set VCC Output == 100Mhz (>100Mhz)==VCO*50=2*50
RCC::PLLCFGR::PLLP0::Pllp6::Set(); //Set PLL Output==16MHz==VCO output/6=100/6
RCC::PLLCFGR::PLLSRC::Set(1);
RCC::CR::HSION::Off::Set();
RCC::CR::PLLON::On::Set();
while(RCC::CR::PLLRDY::Unlocked::IsSet())
{
}
RCC::CFGR::SW::Pll::Set();
while(!RCC::CFGR::SWS::Pll::IsSet())
{
}
RCC::AHB1ENR::GPIOCEN::Enable::Set();
RCC::AHB1ENR::GPIOAEN::Enable::Set();
GPIOC::MODER::MODER13::Input::Set();
GPIOC::MODER::MODER5::Output::Set();
GPIOC::MODER::MODER8::Output::Set();
GPIOC::MODER::MODER9::Output::Set();
GPIOA::MODER::MODER5::Output::Set();
for(;;)
{
if(GPIOC::IDR::IDR13::Low::IsSet())
{
while(GPIOC::IDR::IDR13::Low::IsSet());
if(GPIOC::ODR::ODR5::Low::IsSet())
{
GPIOC::BSRR::BS5::High::Write();
GPIOC::BSRR::BS8::High::Write();
GPIOC::BSRR::BS9::High::Write();
GPIOA::BSRR::BS5::High::Write();

}
else
{
GPIOC::BSRR::BR5::Low::Write();
GPIOC::BSRR::BR8::Low::Write();
GPIOC::BSRR::BR9::Low::Write();
GPIOA::BSRR::BR5::Low::Write();
}
}
}
return 1;
}