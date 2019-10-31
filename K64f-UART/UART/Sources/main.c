/********************************************************/
 /* 
 * Created on: sep 10, 2018
 * Author: Madursk
 * Brief: UART driver for NXP MK64FN1M0VLL12 microcontroller
 */
/******************************************************/




#include "UARTDriver.h"
#define UART_RX_MAILBOX 40u
UART_ModuleConfiguration_st UART_DriverCfg_st;

int main(void)
{
	char_t lcMessage[]={'H','O','L','A',UART_END_TRANSMISSION};
	char_t lcMailbox[UART_RX_MAILBOX];
	UART_DriverCfg_st.aeUART_ActiveChannels[0]=UART3;
	UART_DriverCfg_st.au32UART_Channels_Baudrate[0]=BAUDRATE_115200_;
	vfnUARTInit(&UART_DriverCfg_st);
	vfnUARTInterruptEnable();
	efnUARTWrite(lcMessage);
		
	for(;;) 
	{
		
		if(efnUARTRead(lcMailbox,UART_RX_MAILBOX))
		{
			efnUARTWrite(lcMailbox);
		}
		
	
		
	}
	
	return 0;
}


