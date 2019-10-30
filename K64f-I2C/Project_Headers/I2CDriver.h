/*
 * I2CDriver.h
 *
 *  Created on: Oct 28, 2019
 *      Author: migue
 */

#ifndef I2CDRIVER_H_
#define I2CDRIVER_H_

#include "derivative.h"
#include "datatypes.h"

#define I2C_MODULES 3u
typedef enum
{
    I2C0,
    I2C1,
    I2C3

}I2C_Channels_en;

typedef struct
{
    I2C_Channels_en eI2C_Channel[I2C_MODULES];
    uint32_t u32I2C_Baudrate[I2C_MODULES];
}I2C_ModuleConfiguration_st;

typedef I2C_ModuleConfiguration_st* I2C_ModuleConfigurationPtr;

void I2C_Init(I2C_ModuleConfigurationPtr);
void I2C_Baudrate(I2C_ModuleConfigurationPtr);
void I2C_EnableInterrupts(I2C_ModuleConfigurationPtr);
#endif /* I2CDRIVER_H_ */
