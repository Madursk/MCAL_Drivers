/*******************************************/
 /* UARTDriver.c
 *
 *  Created on: Sep 22, 2018
 *  Author: Madursk
 *  Brief: Functions of UART communication only channel 3 is used
 */
/*****************************************/
#include "UARTDriver.h"



/************************VARIABLES*****************************/
UART_Status_st UART_3_Flags_st;
char_t* cTxBufferPointer;
char_t  cRxBuffer[40];
uint8_t cRxBufferByte;
const char_t cEndOfMessage = '\r';
uint8_t u8TxBufferIndex ;
uint8_t u8RxBufferIndex ;
uint8_t debugData;
/************************************************************/

void UART3_Status_IRQHandler()
{
  
	if(UART_3_Flags_st.TXMODE == 1 && (UART3_S1 & UART_S1_TC_MASK ))
   	{
	   	if(cTxBufferPointer[u8TxBufferIndex] != UART_END_TRANSMISSION)
		{
		    UART3_D = *(cTxBufferPointer + u8TxBufferIndex);
			u8TxBufferIndex++;
			
		}/*Send Byte*/
		else
		{
			u8TxBufferIndex = 0;
			UART_3_Flags_st.TXMODE = 0;
			UART3_C2 ^= UART_C2_TCIE_MASK;
			
		}/*Reset Pointer Index, Disable TC interrupt*/
	
	}/*End Transmission mode*/
	// if(UART3_BDH & UART_S2_RXEDGIF_MASK)
	//  {
	// 	 UART3_S2 |= UART_S2_RXEDGIF_MASK;
	// 	 cRxBuffer[u8RxBufferIndex] = UART3_D;
	//  	if(*(cRxBuffer + u8RxBufferIndex ) == UART_END_RECEPTION)
	// 	{
	// 		u8RxBufferIndex = 0;
	// 		UART_3_Flags_st.RXMODE = 1;
	// 	}
	// 	else u8RxBufferIndex++;
	//   }/*End Reception mode*/
}/*End UART3 Interrupt handler*/



Status_en vfnUARTInit(UART_ModuleConfiguration_stPtr UART_CfgStructPtr)
{
	Status_en eInitializationState = FALSE;
	uint8_t u8UARTChannelsCounter;
	if(!(UART_CfgStructPtr== NULLPTR))
	{
		for(u8UARTChannelsCounter=0; u8UARTChannelsCounter<=UART_HW_UNITS; u8UARTChannelsCounter++ )
		{
			switch((*UART_CfgStructPtr).aeUART_ActiveChannels[u8UARTChannelsCounter])
			{
				case UART0:
				{
					UART0_C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
				}break;
				case UART1:{}break;
				case UART2:{}break;
				case UART3:
				{
					/*Initialization of PORT C Clock and UART3 Clock*/
					SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
					SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
					
					/*PCR16 and PCR17 GPIO multiplexing as Tx and Rx*/
					PORTC_PCR16=PORT_PCR_MUX(U8_UART3_MUX_MODE);
					PORTC_PCR17=PORT_PCR_MUX(U8_UART3_MUX_MODE);

					UART3_C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
					vfnUARTBaudrate( UART_CfgStructPtr);
				}break;
				case UART4:{}break;
				
			}
		}
		
		eInitializationState = TRUE;
	}

	return eInitializationState;
	
	
}/*End UART Receiver and Transmitter Initialization*/

void vfnUARTBaudrate(UART_ModuleConfiguration_stPtr UART_CfgStructPtr)
{
	uint8_t i;
	for(i=0; i<= UART_HW_UNITS; i++)
	{  	
		
		switch((*UART_CfgStructPtr).aeUART_ActiveChannels[i])
				{
					case UART0:{}break;
					case UART1:{}break;
					case UART2:{}break;
					case UART3:
					{
						// UART3_BDH= UART_BDH_SBR(u8fnBDHSearch(lu32Baudrate));
						// UART3_C4 = UART_C4_BRFA(u8fnBRFASearch(lu32Baudrate));
						// UART3_BDL=u8fnBDLSearch(lu32Baudrate);
					}break;
					case UART4:{}break;
				
				}
	// if(BAUDRATE_300_ == lu32Baudrate)
  	// {
  	// 	UART3_BDH= UART_BDH_SBR(BDH_300_);
  	//     UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	// 	UART3_BDL=BDL_300_;
  			    
  	// }
  	// else if (BAUDRATE_600_ == lu32Baudrate)
  	// {
	//    UART3_BDH= UART_BDH_SBR(BDH_600_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	//    UART3_BDL=BDL_600_;
  	// }
  	// else if (BAUDRATE_1200_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_1200_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	//    UART3_BDL=BDL_1200_;
  	// }
  	// else if (BAUDRATE_2400_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_2400_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	//    UART3_BDL=BDL_2400_;
  	// }
  	// else if (BAUDRATE_4800_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_4800_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	//    UART3_BDL=BDL_4800_;
  	// }
  	// else if (BAUDRATE_9600_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_0_);
  	//    UART3_BDL=BDL_9600_;
  	// }
  	// else if (BAUDRATE_14400_ == lu32Baudrate)
    // {
    //    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_14400_);
  	//    UART3_BDL=BDL_14400_;
    // }
    // else if (BAUDRATE_19200_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_128000_);
  	//    UART3_BDL=BDL_128000_;
  		    				
    // }
  	// else if (BAUDRATE_38400_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_38400_);
  	//    UART3_BDL=BDL_38400_;
  	// }
  	// else if (BAUDRATE_57600_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_57600_);
  	//    UART3_BDL=BDL_57600_;
  	// }
  	// else if (BAUDRATE_115200_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_115200_);
  	//    UART3_BDL= BDL_115200_;
  	// }
  	// else if (BAUDRATE_128000_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_128000_);
  	//    UART3_BDL=BDL_128000_;
  	// }
  	// else if (BAUDRATE_256000_ == lu32Baudrate)
  	// {
  	//    UART3_BDH= UART_BDH_SBR(BDH_0_);
  	//    UART3_C4 = UART_C4_BRFA(BRFA_256000_);
  	//    UART3_BDL=BDL_256000_;
  	// }
	}
  		
}/*End UART Baudrate setting*/

void vfnUARTInterruptEnable()
{
	UART3_C2 |= UART_C2_RIE_MASK;
	UART3_S2 |= UART_S2_RXEDGIF_MASK;
	UART3_BDH |= UART_BDH_RXEDGIE_MASK;
	NVICICER1 = 1<<(U8_UART3_IRQ_HANDLER);
	NVICISER1 = 1<<(U8_UART3_IRQ_HANDLER);	
}/*End Tx and Rx Interrupt Enable*/

void vfnUARTErrorsInterruptsEnable()
{
	UART3_C3|= UART_C3_ORIE_MASK | UART_C3_NEIE_MASK | UART_C3_FEIE_MASK 
			|UART_C3_PEIE_MASK;
	NVICICER1 = 1<<(U8_UART3_ERROR_HANDLER);
	NVICISER1 = 1<<(U8_UART3_ERROR_HANDLER);
}/*End Enable Error Sources Interrupt*/ 

Status_en efnUARTRead( char_t* lcRxBufferPointer, uint8_t lu8RxBufferSize)
{
	Status_en leState = FALSE;
	uint8_t lu8IndexCounter = 0;
	if(UART_3_Flags_st.RXMODE == 1)
	{
		while(*(cRxBuffer + lu8IndexCounter) != UART_END_RECEPTION)
		{
			*(lcRxBufferPointer +lu8IndexCounter) = (char_t) *(cRxBuffer + lu8IndexCounter); 
			lu8IndexCounter++;
		}/*End Array copyng from local to function called*/
		if(lu8RxBufferSize > lu8IndexCounter)
		{
			do
			{
				*(lcRxBufferPointer +lu8IndexCounter) = 0;
			}while(lu8IndexCounter++ <= lu8RxBufferSize);
		}
		UART_3_Flags_st.RXMODE = 0;	
		leState = TRUE;
	}/*End Read port when a End of Message was detected*/
	return leState;
}/*End Read UART Port method*/
 

Status_en efnUARTWrite(const char_t lcTxBuffer[])
{
	Status_en leState = FALSE;
	 cTxBufferPointer = lcTxBuffer;
	 if(UART_3_Flags_st.TXMODE == 0)
	 {
		UART_3_Flags_st.TXMODE = 1;
		UART3_C2 |= UART_C2_TCIE_MASK;
		leState = TRUE;
	 }
	 return leState;
	 
}/*End Write UART Port method */
