/********************************************************/
 /* 
 * Created on: sep 10, 2018
 * Author: Madursk
 * Brief: UART driver for Kinetis 64f microcontroller
 */
/******************************************************/




#include "UARTDriver.h"


int main(void)
{
	char_t lcMessage[]={'H','O','L','A',0};
	vfnInitPortClocks();
	vfnPortMux();
	vfnUARTBaudrate(115200u);
	vfnUARTInit();
	vfnUARTInterruptEnable();
	efnUARTWrite(lcMessage);
	
		
	for(;;) 
	{	   
	   	
	}
	
	return 0;
}


