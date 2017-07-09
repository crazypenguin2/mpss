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

int main()
{
    clock rcc_instance;
    timer<tim3> timer_instance{200000};
    timer<tim2> timer_instance2(100000);
    timer<tim3>::oc<ch1> t3oc1({1 , 2});
    timer<tim3>::oc<ch2> t3oc2({1 , 3});
    timer<tim3>::oc<ch3> t3oc3({1 , 4});
    timer<tim3>::oc<ch4> t3oc4({1 , 8});
    timer<tim2>::oc<ch1> t2oc1({1 , 2});
    timer<tim2>::oc<ch2> t2oc2({1 , 3});
    timer<tim2>::oc<ch3> t2oc3({1 , 4});
    timer<tim2>::oc<ch4> t2oc4({1 , 8});

    for( uint16_t i = 0; true; ++i )
    {
    	t3oc1.set_duty(ratio{i, 0xFFFF});
    	t3oc2.set_duty(ratio{i, 0xFFFF});
    	t3oc3.set_duty(ratio{i, 0xFFFF});
    	t3oc4.set_duty(ratio{i, 0xFFFF});
    	t2oc1.set_duty(ratio{i, 0xFFFF});
    	t2oc2.set_duty(ratio{i, 0xFFFF});
    	t2oc3.set_duty(ratio{i, 0xFFFF});
    	t2oc4.set_duty(ratio{i, 0xFFFF});
    	for(uint16_t i = 0; i < 50000; ++i)
    		asm volatile( "nop" );
    }
    while(1)
    {
    }

  return 0;
}
