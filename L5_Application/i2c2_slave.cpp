/*
 * i2c_slave.cpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Sucheta
 */


#include "I2C2_slave.hpp"
#include "LPC17xx.h"
#include "lpc_isr.h"



static void i2c2_slave_isr()
{
    i2c2_slave::getInstance().handleInterrupt();
}

bool i2c2_slave::init(unsigned int speedInKhz, uint8_t* buffer, uint32_t bufferSize)
{
    /**
     * Before I2C is initialized, check to be sure that the I2C wires are logic "1"
     * means that they are pulled high, otherwise there may be a short circuit.
     *
     * I2C2 is on P0.10, and P0.11
     */
    const uint32_t i2c_pin_mask = ( (1<<10) | (1<<11) );
    const bool i2c_wires_are_pulled_high = (i2c_pin_mask == (LPC_GPIO0->FIOPIN & i2c_pin_mask) );

    LPC_PINCON->PINMODE0 &= ~(0xF << 20); // Both pins with Pull-Up Enabled
    LPC_PINCON->PINMODE0 |=  (0xA << 20); // Disable both pull-up and pull-down

    // Enable Open-drain for I2C2 on pins P0.10 and P0.11
    LPC_PINCON->PINMODE_OD0 |= i2c_pin_mask;

    LPC_PINCON->PINSEL0 &= ~(0xF << 20);  // Clear
    LPC_PINCON->PINSEL0 |=  (0xA << 20);  // Enable I2C Pins: SDA, SCL

    lpc_pclk(pclk_i2c2, clkdiv_8);
    const uint32_t pclk = sys_get_cpu_clock() / 8;

    /**
     * I2C wires should be pulled high for normal operation, so if they are, initialize I2C
     * otherwise disable operations on I2C since I2C has a likely hardware BUS fault such as:
     *  - I2C SDA/SCL with no pull-up
     *  - I2C SDA/SCL shorted to ground
     */
    bool status = false;
    if (i2c_wires_are_pulled_high) {
        isr_register(I2C2_IRQn, i2c2_slave_isr);
        status = I2C_Base::slave_init(buffer,bufferSize);
     }
    else {
        disableOperation();
    }
    return status;
}

i2c2_slave::i2c2_slave() : I2C_Base((LPC_I2C_TypeDef*) LPC_I2C2_BASE)
{

}
