/*
 * i2c_slave.hpp
 *
 *  Created on: Mar 27, 2018
 *      Author: Sucheta
 */

#ifndef I2C2_SLAVE_HPP_
#define I2C2_SLAVE_HPP_



#include "singleton_template.hpp"
#include "i2c_base.hpp"



/**
 * I2C2 Singleton Driver
 * This is a thin wrapper around I2C_Base class and merely gives the base
 * address of the I2C2 memory map.
 *
 * @ingroup Drivers
 */
class i2c2_slave : public I2C_Base, public SingletonTemplate<i2c2_slave>
{
    public:
        /// Initializes I2C2 at the given @param speedInKhz
        bool init(unsigned int speedInKhz, uint8_t* buffer, uint32_t bufferSize);

    private:
        i2c2_slave(); ///< Private constructor for this singleton class
        friend class SingletonTemplate<i2c2_slave>;  ///< Friend class used for Singleton Template
};



#endif /* I2C2_SLAVE_HPP_ */
