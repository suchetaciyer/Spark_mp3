/*
 * VS1053B.c
 *
 *  Created on: Apr 24, 2018
 *      Author: Sneha
 */
#include "VS1053B.hpp"
#include "LPC17xx.h"
#include "LabGPIO.hpp"
#include "utilities.h"

LabGPIO chipSelect = LabGPIO(1, 22);
LabGPIO dataChipSelect = LabGPIO(1, 20);
LabGPIO chipReset = LabGPIO(1, 19);
LabGPIO dreqPin = LabGPIO(2, 7);


//enabling Chip select by writing a low to pin P1.22
void mp3_cs()
{
    chipSelect.setAsOutput();
    chipSelect.setLow();
    /*LPC_PINCON->PINSEL3 &= ~(3 << 12); //reset bits 12 and 13 in PINSEL3 for GPIO on pin P1.22
     LPC_GPIO1->FIODIR |= (1 << 22); //set as output - P1.22
     LPC_GPIO1->FIOCLR |= (1 << 22); //set as 0 to select  P1.22*/
}

//disabling Chip select by writing a high to pin P1.22
void mp3_ds()
{
    chipSelect.setHigh();
    //LPC_GPIO1->FIOSET |= (1 << 22); //set as 1 to de-select
}

//enabling Chip select by writing a low to pin P1.20
void mp3_data_cs()
{
    dataChipSelect.setAsOutput();
    dataChipSelect.setLow();
    /*LPC_PINCON->PINSEL3 &= ~(3 << 8); //reset bits 8 and 9 in PINSEL3 for GPIO on pin P1.22
     LPC_GPIO1->FIODIR |= (1 << 20); //set as output - P1.20
     LPC_GPIO1->FIOCLR |= (1 << 20); //set as 0 to select  P1.20*/
}

//disabling Chip select by writing a low to pin P1.20
void mp3_data_ds()
{
    dataChipSelect.setHigh();
    //LPC_GPIO1->FIOSET |= (1 << 20); //set as 1 to de-select
}

//reset
void mp3_reset()
{
    chipReset.setAsOutput();
    chipReset.setLow(); //enable the reset pin
    delay_ms(20);
    chipReset.setHigh(); //disable the reset pin - working mode on
    delay_ms(20);
}

void mp3_hardwareReset()
{
    /*doing a hardware reset*/
    mp3_ds();
    mp3_data_ds();
    mp3_reset(); //reset the mp3 shield

}

//enabling Chip select by writing a low to pin P2.7
void mp3_dreq_init()
{
    dreqPin.setAsInput();
 }

bool mp3_dreq_getLevel()
{
    return dreqPin.getLevel();
}

bool mp3_initDecoder()
{
    mp3_writeRequest(SCI_MODE, 0x4800);
    mp3_writeRequest(SCI_CLOCKF, 0xBBE8); //was 9800, EBE8, B3E8, BBE8
    mp3_writeRequest(SCI_VOL, 0x0000); //full vol
    mp3_writeRequest(SCI_BASS, 0x00F6);
    mp3_writeRequest(SCI_AUDATA, 0xAC80); //for stereo decoding, AC45

    return false;
}

