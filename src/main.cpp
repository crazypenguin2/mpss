#include "main.hpp"
#include "adc.hpp"
#include "isr.hpp"
#include "usart.hpp"
#include "startup.hpp"
#include "display.hpp"
#include "timer.hpp"

class clock
{

public:
    clock()
    {
        RCC_PCLK2Config(RCC_HCLK_Div2);
    }
};

template <typename N = none>
struct uint16_t_to_ratio : N
{
  void handler(uint16_t value) 
  {
    static_cast<N*>(this)->handler(ratio{value, 4095});
  }
};

template <>
struct uint16_t_to_ratio<none> {};

uint8_t frequencies[] = {18, 22, 27, 33, 39, 47, 56, 68, 82, 100, 120, 150, 180, 220};

int main()
{
/*    clock rcc_instance;
    //timer<tim3> timer_instance{200000};
    timer<tim2> timer_instance2(18);
    //timer<tim3>::oc<ch1> t3oc1({1 , 2});
    //timer<tim3>::oc<ch2> t3oc2({1 , 3});
    //timer<tim3>::oc<ch3> t3oc3({1 , 4});
    //timer<tim3>::oc<ch4> t3oc4({1 , 8});
    timer<tim2>::oc<ch1> t2oc1({1 , 2});
    //timer<tim2>::oc<ch2> t2oc2({1 , 3});
    //timer<tim2>::oc<ch3> t2oc3({1 , 4});
    //timer<tim2>::oc<ch4> t2oc4({1 , 8});

    for( uint8_t i = 0;; i == 13 ? i = 0 : ++i )
    {
        for(uint32_t j = 0; j < SystemCoreClock; ++j)
            asm volatile( "nop" );
        timer_instance2.set_frequency(frequencies[i]);
    }*/

/*  using T1 = timer<tim2>::oc<ch1>;
  using T0 = timer<tim3>::ic<ch1>;
  auto equivalent_pulse = make_pipe(T0{}, T1{});
*/
  using T2 = timer<tim1>::oc<ch1_t>;
  using ADC0 = adc<>;
  auto voltage_driven_pwm = make_pipe(ADC0{}, uint16_t_to_ratio<>{}, T2{});
  
  while(1)
  {
  }

  return 0;
}
