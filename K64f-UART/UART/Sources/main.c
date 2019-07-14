/********************************************************/
 /* 
 * Created on: sep 10, 2018
 * Author: Madursk
 * Brief: UART driver for NXP MK64FN1M0VLL12 microcontroller
 */
/******************************************************/




#include "UARTDriver.h"


int main(void)
{
	char_t lcMessage[]={'H','O','L','A',0};
	vfnInitPortClocks();
	vfnPortMux();
	vfnUARTBaudrate(BAUDRATE_115200_);
	vfnUARTInit();
	vfnUARTInterruptEnable();
	efnUARTWrite(lcMessage);
	
		
	for(;;) 
	{	   
	   	
	}
	
	return 0;
}


