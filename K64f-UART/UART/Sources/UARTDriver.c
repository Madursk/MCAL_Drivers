/*******************************************/
 /* UARTDriver.c
 *
 *  Created on: Sep 22, 2018
 *  Author: Madursk
 *  Brief: Functions of UART communication
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
	uint8_t u8BaudrateCfgIndex;
	for(u8BaudrateCfgIndex=0; u8BaudrateCfgIndex<= UART_HW_UNITS; u8BaudrateCfgIndex++)
	{  	
		
		switch((*UART_CfgStructPtr).aeUART_ActiveChannels[u8BaudrateCfgIndex])
				{
					case UART0:
					{
						UART0_BDH= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART0_C4 = UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART0_BDL=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART1:
					{
						UART1_BDH= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART1_C4 = UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART1_BDL=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART2:
					{
						UART2_BDH= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART2_C4 = UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART2_BDL=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART3:
					{
						UART3_BDH= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART3_C4 = UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART3_BDL=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART4:
					{
						UART4_BDH= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART4_C4 = UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART4_BDL=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;
				
				}
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

uint8_t u8fnBDHSearch(uint32_t lu32Baudrate)
{
	uint8_t u8BDH=BDH_0_;
	if(BAUDRATE_9600_ < lu32Baudrate )
	{
		switch(lu32Baudrate)
		{
			case BAUDRATE_300_:
			{
				u8BDH = BDH_300_;
			}break;

			case BAUDRATE_600_:
			{
				u8BDH = BDH_600_;
			}break;
				
			case BAUDRATE_1200_:
			{
				u8BDH= BDH_1200_;
			}break;
				
			case BAUDRATE_2400_:
			{
				u8BDH = BDH_2400_;
			}break;

			case BAUDRATE_4800_:
			{
				u8BDH = BDH_4800_;
			}break;
		}
	}
	return u8BDH;
}

uint8_t u8fnBRFASearch(uint32_t lu32Baudrate)
{
	uint8_t u8BRFA= BRFA_0_;
	if(BAUDRATE_14400_ < lu32Baudrate)
	{
			switch(lu32Baudrate)
		{
			case BAUDRATE_19200_:
			{
				u8BRFA = BRFA_19200_;
			}break;
			
			case BAUDRATE_38400_:
			{
				u8BRFA = BRFA_38400_;
			}break;
			
			case BAUDRATE_57600_:
			{
				u8BRFA = BRFA_57600_;
			}break;
			
			case BAUDRATE_115200_:
			{
				u8BRFA = BRFA_115200_;
			}break;
			
			case BAUDRATE_128000_:
			{
				u8BRFA = BRFA_128000_;
			}break;

			case BAUDRATE_256000_:
			{
				u8BRFA = BRFA_256000_;
			}break;
		}
	}
	
	return u8BRFA;
}
uint8_t u8fnBDLSearch(uint32_t lu32Baudrate)
{
	uint8_t u8BDL=0;
	switch(lu32Baudrate)
	{
		case BAUDRATE_300_:
		{
			u8BDL = BDL_300_;
		}break;
		
		case BAUDRATE_600_:
		{
			u8BDL = BDL_600_;
		}break;

		case BAUDRATE_1200_:
		{
			u8BDL = BDL_1200_;
		}break;

		case BAUDRATE_2400_:
		{
			u8BDL = BDL_2400_;
		}break;

		case BAUDRATE_4800_:
		{
			u8BDL = BDL_4800_;
		}break;

		case BAUDRATE_9600_:
		{
			u8BDL = BDL_9600_;
		}break;
		
		case BAUDRATE_14400_:
		{
			u8BDL = BDL_14400_;
		}break;
		
		case BAUDRATE_19200_:
		{
			u8BDL = BDL_19200_;
		}break;
		
		case BAUDRATE_38400_:
		{
			u8BDL = BDL_38400_;
		}break;
		
		case BAUDRATE_57600_:
		{
			u8BDL = BDL_57600_;
		}break;
		
		case BAUDRATE_115200_:
		{
			u8BDL = BDL_115200_;
		}break;
		
		case BAUDRATE_128000_:
		{
			u8BDL = BDL_128000_;
		}break;

		case BAUDRATE_256000_:
		{
			u8BDL = BDL_256000_;
		}break;
	}
	return u8BDL;
}