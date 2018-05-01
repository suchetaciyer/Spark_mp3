/*
 * ADCDriver.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: Sucheta
 */

#include "ADCDriver.hpp"
#include "printf_lib.h"

ADCDriver::ADCDriver() {;}

void ADCDriver::adcSelectPin(ADC_PIN adc_pin_arg)
{
    if(adc_pin_arg == (ADC_PIN::ADC_PIN_0_25))
    {
        LPC_PINCON->PINSEL1 &= ~(1<<19);
        LPC_PINCON->PINSEL1 |= (1<<18);//Set bits [19:18] to 01 to select AD0.2 - light sensor
    }
    else if(adc_pin_arg == (ADC_PIN::ADC_PIN_0_26))
    {
        LPC_PINCON->PINSEL1 &= ~(1<<21);
        LPC_PINCON->PINSEL1 |= (1<<20);//Set bits [21:20] to 01 to select AD0.3
    }
    else if(adc_pin_arg == (ADC_PIN::ADC_PIN_1_30))
    {
       LPC_PINCON->PINSEL3 |= (1<<29);
       LPC_PINCON->PINSEL3 |= (1<<28);//Set bits [29:28] to 11 to select AD0.4
    }
    else if(adc_pin_arg == (ADC_PIN::ADC_PIN_1_31))
    {
       LPC_PINCON->PINSEL3 |= (1<<31);
       LPC_PINCON->PINSEL3 |= (1<<30);//Set bits [31:30] to 11 to select AD0.5
    }
}

void ADCDriver::adcInitBurstMode()
{
    LPC_SC->PCONP |= (1<<12); //Select bit 12 for PCADC bit to be set
    LPC_ADC->ADCR |= (1<<21); //Select bit 21 for PDN bit to be set to select ADC functionality
    LPC_SC->PCLKSEL0 |= (1<<25);
    LPC_SC->PCLKSEL0 |= (1<<24); //Set bits [25:24] to 11 to select clock = clock/8;
    LPC_ADC->ADCR &= ~(7<<24);//Set the start bit to 000 before setting the burst mode on
    LPC_ADC->ADCR |= (1<<3);//Set bit 3 to select AD0.3
    LPC_ADC->ADCR |= (1<<16); //Set the burst mode bit
    LPC_ADC->ADINTEN &= ~(1<<8);// If BURST is set to 1,reset set the ADGINTEN bit in the AD0INTEN register.
}

float ADCDriver::readADCVoltageByChannel(uint8_t adc_channel_arg)
{
    uint32_t temp = LPC_ADC->ADCR & 0x000F;
    //u0_dbg_printf("temp = %d",temp);
    if(adc_channel_arg == 2)
    {
        while(!(LPC_ADC->ADDR2 & (1<<31)));  //Bit 31 is the DONE flag
            return (((LPC_ADC->ADDR2)>>4) & 0xFFF);
    }
    if(adc_channel_arg == 3)
    {

        while(!(LPC_ADC->ADDR3 & (1<<31)));  //Bit 31 is the DONE flag
            return (((LPC_ADC->ADDR3)>>4) & 0xFFF);
    }
    if(adc_channel_arg == 4)
    {
        while(LPC_ADC->ADDR4 & (1<<31))  //Bit 31 is the DONE flag
            {return (((LPC_ADC->ADDR4)>>4) & 0xFFF);}
    }
    if(adc_channel_arg == 5)
    {
        while(LPC_ADC->ADDR5 & (1<<31))  //Bit 31 is the DONE flag
            {return (((LPC_ADC->ADDR5)>>4) & 0xFFF);}
    }
    return 0;
}
