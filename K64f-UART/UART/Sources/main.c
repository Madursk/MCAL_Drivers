/********************************************************/
 /* 
 * Created on: sep 10, 2018
 * Author: Madursk
 * Brief: UART driver for NXP MK64FN1M0VLL12 microcontroller
 */
/******************************************************/




#include "UARTDriver.h"
#define UART_RX_MAILBOX 40u

int main(void)
{
	char_t lcMessage[]={'H','O','L','A',UART_END_TRANSMISSION};
	char_t lcMailbox[UART_RX_MAILBOX];
	vfnUARTInitPortClocks();
	vfnUARTPortMux();
	vfnUARTBaudrate(BAUDRATE_115200_);
	vfnUARTInit();
	vfnUARTInterruptEnable();
	efnUARTWrite(lcMessage);
		
	for(;;) 
	{
		
		if(efnUARTRead(lcMailbox,UART_RX_MAILBOX))
		{
			efnUARTWrite(lcMailbox);
		}
		else
		{
			/*Do Nothing */
		}
		
	
		
	}
	
	return 0;
}


void NMI_Handler() 
{

}
void HardFault_Handler()
{

}
void Mem_Manage_Fault_Handler() 
{

}
void Bus_Fault_Handler() 
{

}
void Usage_Fault_Handler() 
{

}
void SVC_Handler()
{

}
void DebugMonitor_Handler() 
{

}
void PendSV_Handler() 
{

}
void SysTick_Handler() 
{

}