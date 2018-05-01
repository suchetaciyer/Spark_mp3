/*
 * PWMDriver.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: Sucheta
 */


#include "PWMDriver.hpp"


   /**
    * 1) Select PWM functionality on all PWM-able pins.
    */
    void PWMDriver::pwmSelectAllPins()
    {
        LPC_SC->PCONP |= (1<<6); //Select bit 6 for PCPWM1 bit to be set

        LPC_SC->PCLKSEL0 &= ~(0x3 << 12);
        LPC_SC->PCLKSEL0 |= (1 << 12); //[13:12] = 01 PCLK_PWM1(CLK=CLK)

        //Select PWM function on pins P2.0 to P2.5
        LPC_PINCON->PINSEL4 &= ~(0xFFF);    //Clear all the bits
        LPC_PINCON->PINSEL4 |= 0x555;       //Then set 6 two-set bits to 01
    }

    /**
    * 1) Select PWM functionality of pwm_pin_arg
    *
    * @param pwm_pin_arg is the PWM_PIN enumeration of the desired pin.
    */
    void PWMDriver::pwmSelectPin(PWM_PIN pwm_pin_arg)
    {
        LPC_SC->PCONP |= (1<<6); //Select bit 6 for PCPWM1 bit to be set
        LPC_SC->PCLKSEL0 &= ~(3<<12); // [13:12] = 11 PCLK_PWM1(CLK=CLK/8)

        //Initialize PWM channel 1 - PWM1.1[1:0] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<1);
        LPC_PINCON->PINSEL4 |= 1;

        //Initialize PWM channel 1 - PWM1.2[3:2] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<3);
        LPC_PINCON->PINSEL4 |= (1<<2);

        //Initialize PWM channel 1 - PWM1.3[5:4] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<5);
        LPC_PINCON->PINSEL4 |= (1<<4);

        //Initialize PWM channel 1 - PWM1.4[7:6] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<7);
        LPC_PINCON->PINSEL4 |= (1<<6);

        //Initialize PWM channel 1 - PWM1.5[9:8] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<9);
        LPC_PINCON->PINSEL4 |= (1<<8);

        //Initialize PWM channel 1 - PWM1.6[11:10] = 01
        LPC_PINCON->PINSEL4 &= ~(1<<11);
        LPC_PINCON->PINSEL4 |= (1<<10);
    }

    /**
    * Initialize your PWM peripherals.  See the notes here:
    * http://books.socialledge.com/books/embedded-drivers-real-time-operating-systems/page/pwm-%28pulse-width-modulation%29
    *
    * In general, you init the PWM peripheral, its frequency, and initialize your PWM channels and set them to 0% duty cycle
    *
    * @param frequency_Hz is the initial frequency in Hz.
    *
    */
    void PWMDriver::pwmInitSingleEdgeMode(uint32_t frequency_Hz, PWM_PIN pwm_pin_arg)
    {
        //Select duty cycle for all the channels to be 0 i.e set MR0 = 0 for all the 6 values
        //LPC_PWM1->MR0

        //When TC == MR0 -->> (single edge pin = 1 , MR0 = reset). To ebnable this function, we do ..
        LPC_PWM1->MCR = (1 << 1);

        //set the MR0 register to set the frequency
        setFrequency(frequency_Hz);

        //enable the PWM output and make it single edge mode, set duty cycle to 0

        /*A match with MRn clears PWMn in single edge mode. Setting this to 0 means a constant high*/

        if(pwm_pin_arg == PWM_PIN_2_0)//PWM 1.1 output enabled
        {
          LPC_PWM1->PCR |= (1 << 9); //this is always single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR1 =0;
        }

        else if(pwm_pin_arg == PWM_PIN_2_1)//PWM 1.2 output enabled
        {
          LPC_PWM1->PCR |= (1 << 10);
          //enable single edge mode
          LPC_PWM1->PCR &= ~(1 << 2); //reset bit 2 for single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR2 =0;
        }
        else if(pwm_pin_arg == PWM_PIN_2_2)//PWM 1.3 output enabled
        {
          LPC_PWM1->PCR |= (1 << 11);
          //enable single edge mode
          LPC_PWM1->PCR &= ~(1 << 3); //reset bit 3 for single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR3 =0;
        }

        else if(pwm_pin_arg == PWM_PIN_2_3)//PWM 1.4 output enabled
        {
          LPC_PWM1->PCR |= (1 << 12);
          //enable single edge mode
          LPC_PWM1->PCR &= ~(1 << 4); //reset bit 4 for single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR4 =0;
        }

        else if(pwm_pin_arg == PWM_PIN_2_4)//PWM 1.5 output enabled
        {
          LPC_PWM1->PCR |= (1 << 13);
          //enable single edge mode
          LPC_PWM1->PCR &= ~(1 << 5); //reset bit 5 for single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR5 =0;
        }
        else if(pwm_pin_arg == PWM_PIN_2_5)//PWM 1.6 output enabled
        {
          LPC_PWM1->PCR |= (1 << 14);
          //enable single edge mode
          LPC_PWM1->PCR &= ~(1 << 6); //reset bit 6 for single edge mode
          //set 0% duty cycle
          LPC_PWM1->MR6 =0;
        }

        /*init the PWM peripheral*/
        //enable PWM in the PWM1TCR
        LPC_PWM1->TCR |= (1<<3); //enable PWM
        LPC_PWM1->TCR |= (1<<0); //enable counter

        //Note, here we set all the parameters first and then enable the counter.
    }

    void PWMDriver::setDutyCycle(PWM_PIN pwm_pin_arg, float duty_cycle_percentage)
    {
        /*
         * If MRx == match value --> PWMx pin = 0 in single edge mode
         * duty cycle is a percentage of the total cycle value set in MR0
         * */
        uint32_t total_cycle_time = LPC_PWM1->MR0;
        uint32_t value_to_set_dutycycle = (duty_cycle_percentage * total_cycle_time)/100;

        if(duty_cycle_percentage > 100)
        {
            u0_dbg_printf("DS to set is >100 (%f)",duty_cycle_percentage);
                return ;
            }
        if(pwm_pin_arg == PWM_PIN_2_0) //MR1 will clear this - PWM1
        {
            LPC_PWM1->MR1 = value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 1);
        }
        else if(pwm_pin_arg == PWM_PIN_2_1) //MR2 will clear this - PWM2
        {
            LPC_PWM1->MR2 = value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 2);
        }
        else if(pwm_pin_arg == PWM_PIN_2_2) //MR3 will clear this - PWM3
        {
            LPC_PWM1->MR3 = value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 3);
        }
        else if(pwm_pin_arg == PWM_PIN_2_3) //MR4 will clear this - PWM4
        {
            LPC_PWM1->MR4= value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 4);
        }
        else if(pwm_pin_arg == PWM_PIN_2_4) //MR5 will clear this - PWM5
        {
            LPC_PWM1->MR5 = value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 5);
        }
        else if(pwm_pin_arg == PWM_PIN_2_5) //MR6 will clear this - PWM6
        {
            LPC_PWM1->MR6= value_to_set_dutycycle;
            LPC_PWM1->LER |= (1 << 6);
        }
    }

    float PWMDriver::getDutyCycle(PWM_PIN pwm_pin_arg)
    {
        if(pwm_pin_arg == PWM_PIN_2_0)
        {
           return (LPC_PWM1->MR1 * 100 /LPC_PWM1->MR0);
        }
        else if(pwm_pin_arg == PWM_PIN_2_1)
        {
           return (LPC_PWM1->MR2 * 100 /LPC_PWM1->MR0);
        }
        else if(pwm_pin_arg == PWM_PIN_2_2)
        {
           return (LPC_PWM1->MR3 * 100 /LPC_PWM1->MR0);
        }
        else if(pwm_pin_arg == PWM_PIN_2_3)
        {
           return (LPC_PWM1->MR4 * 100 /LPC_PWM1->MR0);
        }
        else if(pwm_pin_arg == PWM_PIN_2_4)
        {
           return (LPC_PWM1->MR5 * 100 /LPC_PWM1->MR0);
        }
        else if(pwm_pin_arg == PWM_PIN_2_5)
        {
           return (LPC_PWM1->MR6 * 100 /LPC_PWM1->MR0);
        }
        else return 0;
    }


    /**
    * Optional:
    * 1) Convert frequency_Hz to the appropriate match register value
    * 2) Assign the above value to MR0
    *
    * @param frequency_hz is the desired frequency of all pwm pins
    */
    void PWMDriver::setFrequency(uint32_t frequency_Hz)
    {
        //Clock freq = F, Req. Clock Freq = F/2 then the match control reg (MCR) = F/(F/4) = 4

         uint32_t sys_clock = sys_get_cpu_clock(); //The CPU clock frequency is 96MHz
         uint32_t set_value_for_MR0 = sys_clock/frequency_Hz;
         LPC_PWM1->MR0 = set_value_for_MR0;
         //LPC_PWM1->LER |= (1 << 0); //enabling the latch
    }
