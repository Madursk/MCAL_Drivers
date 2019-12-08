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
char_t cTxBuffer[40];
char_t  cRxBuffer[40];
uint8_t cRxBufferByte;
const char_t cEndOfMessage = '\r';
uint8_t u8TxBufferIndex ;
uint8_t u8RxBufferIndex ;
uint8_t debugData;
/************************************************************/

void UART3_Status_IRQHandler()
{

		if((UART3_S1 & UART_S1_TDRE_MASK) && UART_3_Flags_st.TXMODE==1)
		{
			 if(UART_END_TRANSMISSION != cTxBuffer[u8TxBufferIndex])
			 {
				 UART3_D = cTxBuffer[u8TxBufferIndex];
		 		u8TxBufferIndex++;
				
			 }
			 else
			 {
				 u8TxBufferIndex = 0;
				 UART3_C2 ^= UART_C2_TIE_MASK;
				 UART_3_Flags_st.TXMODE = 0;
			 }
		}	 


		if(UART3_S1 & UART_S1_RDRF_MASK)
		{
			 
				cRxBuffer[u8RxBufferIndex] = UART3_D;
				

			if(UART_END_RECEPTION == cRxBuffer[u8RxBufferIndex] )
			{
				u8RxBufferIndex = 0;
				UART_3_Flags_st.RXMODE = 1;
			}
			else
			{
				u8RxBufferIndex++;
			}
		
			
		}




}/*End UART3 Interrupt handler*/



UART_Status_en* vfnUARTInit(UART_ModuleConfiguration_stPtr UART_CfgStructPtr)
{
	UART_Status_en eUART_Status[UART_HW_UNITS];
	uint8_t u8UARTChannelsCounter;
	uint16_t ubd;					/*Variable to save the baud rate*/
	uint8_t temp;
	
	if(!(UART_CfgStructPtr== NULLPTR))
	{
		for(u8UARTChannelsCounter=0; u8UARTChannelsCounter<=UART_HW_UNITS; u8UARTChannelsCounter++ )
		{
			
			if((*UART_CfgStructPtr).aeUART_ActiveChannels[u8UARTChannelsCounter]==UART_ACTIVE)
			{
				switch(u8UARTChannelsCounter)
				{
					case UART0:
					{
						/*Implementation TBD*/
					}break;
					case UART1:{ /*Implementation TBD*/ }break;
					case UART2:{ /*Implementation TBD*/ }break;
					case UART3:
					{
						eUART_Status[u8UARTChannelsCounter] = UART_UNINITIALIZED;

						/*Initialization of PORT C Clock and UART3 Clock*/
						SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
						SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
						
						/*PCR16 and PCR17 GPIO multiplexing as Tx and Rx*/
						PORTC_PCR16=PORT_PCR_MUX(U8_UART3_MUX_MODE);
						PORTC_PCR17=PORT_PCR_MUX(U8_UART3_MUX_MODE);
						UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
						if((*UART_CfgStructPtr).aeUART_Channels_FIFOS[u8UARTChannelsCounter] == ONE_DATAWORD )
						{
							UART3_PFIFO |= UART_PFIFO_TXFE_MASK;
							UART3_CFIFO |= (UART_CFIFO_RXFLUSH_MASK | UART_CFIFO_TXFLUSH_MASK);

							if ((*UART_CfgStructPtr).aeUART_Channel_Parity[u8UARTChannelsCounter] == PARITY_INACTIVE)
							{
								if((*UART_CfgStructPtr).aeUART_Channels_Handshake[u8UARTChannelsCounter] ==HANDSHAKE_INACTIVE)
								{
									if((*UART_CfgStructPtr).aeUART_Channels_IRDAs[u8UARTChannelsCounter] ==IRDA_INACTIVE)
									{
										vfnUARTBaudrate(UART_CfgStructPtr);
										// ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */
										// temp = UART3_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
										// UART3_BDH = temp | (((ubd & 0x1F00) >> 8));
										// UART3_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);
										vfnUARTInterruptEnable();
										UART3_C2 |=  (UART_C2_TE_MASK | UART_C2_RE_MASK );
										eUART_Status[u8UARTChannelsCounter] = UART_INITIALIZED;
									}
									else if (IRDA_ACTIVE)
									{
										/*Implementation TBD*/
									}

									else
									{
										eUART_Status[u8UARTChannelsCounter] = UART_IRDA_CFG_MISMTCH;
									}
									
									
								}
								else if((*UART_CfgStructPtr).aeUART_Channels_Handshake ==RTS_CTS)
								{
									/*Implementation TBD*/
								}
								else
								{
									eUART_Status[u8UARTChannelsCounter] = UART_HANDSHAKE_CFG_MISMTCH;
								}
								
							}
							else if ((*UART_CfgStructPtr).aeUART_Channel_Parity == EVEN)
							{
								/*Implementation TBD*/
							}
							else if ((*UART_CfgStructPtr).aeUART_Channel_Parity == ODD)
							{
								/*Implementation TBD*/
							}
							else
							{
								eUART_Status[u8UARTChannelsCounter] = UART_PARITY_CFG_MISMTCH;
							}
						}
						else
						{
							eUART_Status[u8UARTChannelsCounter] = UART_FIFOS_CFG_MISMTCH;
						}
						
					}break;
					case UART4:
					{
						/*Implementation TBD*/
					}break;
					
				}
			}

		}
		
	}
	return eUART_Status;
	
	
}/*End UART Receiver and Transmitter Initialization*/

void vfnUARTBaudrate(UART_ModuleConfiguration_stPtr UART_CfgStructPtr)
{
	uint8_t u8BaudrateCfgIndex;
	for(u8BaudrateCfgIndex=0; u8BaudrateCfgIndex<= UART_HW_UNITS; u8BaudrateCfgIndex++)
	{  	
		
		if((*UART_CfgStructPtr).aeUART_ActiveChannels[u8BaudrateCfgIndex]==UART_ACTIVE)
		{
			switch(u8BaudrateCfgIndex)
				{
					case UART0:
					{
						UART0_BDH |= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART0_C4 |= UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART0_BDL|=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART1:
					{
						UART1_BDH|= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART1_C4 |= UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART1_BDL|=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART2:
					{
						UART2_BDH|= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART2_C4 |= UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART2_BDL|=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART3:
					{
						UART3_BDH|= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART3_C4 |= UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART3_BDL|=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;

					case UART4:
					{
						UART4_BDH|= UART_BDH_SBR(u8fnBDHSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART4_C4 |= UART_C4_BRFA(u8fnBRFASearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]));
						UART4_BDL|=u8fnBDLSearch((*UART_CfgStructPtr).au32UART_Channels_Baudrate[u8BaudrateCfgIndex]);
					}break;
				
				}
		}
	}
  		
}/*End UART Baudrate setting*/

void vfnUARTInterruptEnable()
{
	UART3_C2 |= UART_C2_RIE_MASK;
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

std_ReturnType u8fnUARTRead( char_t lcRxBuffer[], uint8_t lu8RxBufferSize)
{
	std_ReturnType lu8State = E_NOT_OK;
	uint8_t lu8IndexCounter = 0;
	if( 1 == UART_3_Flags_st.RXMODE)
	{
		do
		{
			lcRxBuffer[lu8IndexCounter] = cRxBuffer[lu8IndexCounter];
			
		}while(lu8IndexCounter++ <= lu8RxBufferSize  );
		UART_3_Flags_st.RXMODE= 0;
		lu8State = E_OK;
	}
	
	return lu8State;
}/*End Read UART Port method*/
 

std_ReturnType u8fnUARTWrite(char_t lcTxBuffer[])
{
	std_ReturnType lu8State = E_NOT_OK;
	uint8_t u8MailboxInterchangeCounter = 0;
	
	if(0 == UART_3_Flags_st.TXMODE)
	{

		do
		{
			cTxBuffer[u8MailboxInterchangeCounter] = lcTxBuffer[u8MailboxInterchangeCounter];
			
		}while(UART_END_TRANSMISSION != lcTxBuffer[u8MailboxInterchangeCounter++]);
		lu8State = E_OK;
		UART_3_Flags_st.TXMODE = 1;
		UART3_C2 |= UART_C2_TIE_MASK;
	 }
	 return lu8State;
	 
}/*End Write UART Port method */

uint8_t u8fnBDHSearch(uint32_t lu32Baudrate)
{
	uint8_t u8BDH=BDH_0_;
#if BUS_CLOCK == 20000000L
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

			case BAUDRATE_9600_:
			{
				u8BDH = BAUDRATE_9600_;
			}break;

			default:
			{
				u8BDH=BDH_0_;
			}break;
		}
#else
	/* Custom Implementation */
#endif
	return u8BDH;
}

uint8_t u8fnBRFASearch(uint32_t lu32Baudrate)
{
	uint8_t u8BRFA= BRFA_0_;
#if BUS_CLOCK == 20000000L
		switch(lu32Baudrate)
		{
			case BAUDRATE_600_:
			{
				u8BRFA = BRFA_600_;
			}break;

			case BAUDRATE_1200_:
			{
				u8BRFA = BRFA_1200_;
			}break;

			case BAUDRATE_2400_:
			{
				u8BRFA = BRFA_2400_;
			}break;

			case BAUDRATE_4800_:
			{
				u8BRFA = BRFA_4800_;
			}break;

			case BAUDRATE_9600_:
			{
				u8BRFA = BRFA_9600_;
			}break;

			case BAUDRATE_14400_:
			{
				u8BRFA = BRFA_14400_;
			}break;

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
#else
	/* Custom Implementation */
#endif
	
	return u8BRFA;
}
uint8_t u8fnBDLSearch(uint32_t lu32Baudrate)
{
	uint8_t u8BDL=0;
#if BUS_CLOCK == 20000000L
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
#else
	/* Custom Implementation */
#endif
	return u8BDL;
}