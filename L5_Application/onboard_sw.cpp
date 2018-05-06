/*
 * onboard_sw.c
 *
 *  Created on: May 5, 2018
 *      Author: Sucheta
 */

#include "LPC17xx.h"
#include "LabGPIO.hpp"
//#include "utilities.h"

LabGPIO brdSW0 = LabGPIO(1,9); /*Internal switch is hardwired to GPIO port 1.9*/
LabGPIO brdSW1 = LabGPIO(1,10); /*Internal switch is hardwired to GPIO port 1.10*/
LabGPIO brdSW2 = LabGPIO(1,14); /*Internal switch is hardwired to GPIO port 1.14*/
LabGPIO brdSW3 = LabGPIO(1,15); /*Internal switch is hardwired to GPIO port 1.15*/

//All the switches have to be set as input
void onboard_sw_set_direction()
{
    brdSW0.setAsInput();
    brdSW1.setAsInput();
    brdSW2.setAsInput();
    brdSW3.setAsInput();
}
