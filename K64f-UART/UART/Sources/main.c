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
	char_t lcMessage[]={'H','E','L','L','O',' ','W','O','R','L','D',UART_END_TRANSMISSION};
	char_t lcMailbox[UART_RX_MAILBOX];
	UART_DriverCfg_st.aeUART_ActiveChannels[UART3]=UART_ACTIVE;
	UART_DriverCfg_st.au32UART_Channels_Baudrate[UART3]=BAUDRATE_9600_;
	UART_DriverCfg_st.aeUART_Channels_FIFOS[UART3] = ONE_DATAWORD;
	vfnUARTInit(&UART_DriverCfg_st);
	u8fnUARTWrite(lcMessage);
		
	for(;;) 
	{
		if(u8fnUARTRead(lcMailbox, UART_RX_MAILBOX) == E_OK)
		{
			u8fnUARTWrite(lcMailbox);
		}
		
		
	}
	
	return 0;
}

