/*
 * main implementation: use this 'C' sample to create your own application
 *
 */




#include "I2CDriver.h"

I2C_ModuleConfiguration_st I2C_DriverCfg_st;
void I2C_Cfg(void);


int main(void)
{
	
	I2C_Cfg();
	I2C_Init(&I2C_DriverCfg_st);
	
	
	
	
	for(;;) {	   
	
	}
	
	return 0;
}

void I2C_Cfg(void)
{
	I2C_DriverCfg_st.eI2C_Channel[0] = I2C0;
	I2C_DriverCfg_st.u32I2C_Baudrate[0]=100;
}