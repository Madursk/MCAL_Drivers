/*
 * UARTDriver.h
 *
 *  Created on: Sep 22, 2018
 *  Author: Madursk
 *  Brief: Header for the UART Driver C file
 *  Note: The BRFA bits and the UART calculations DEPEND on
 *  the UART Module clock,  in this case 20 Mhz, it will vary,
 *  recalculate accordingly and define it.
 */

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

#include "datatypes.h"
#include "derivative.h"
#include "ProjectClocks.h"

/*********************** MACROS *********************************/
#define UART_HW_UNITS 5u

#define BAUDRATE_300_   300u
#define BAUDRATE_600_   600u
#define BAUDRATE_1200_  1200u
#define BAUDRATE_2400_  2400u
#define BAUDRATE_4800_  4800u
#define BAUDRATE_9600_  9600u
#define BAUDRATE_14400_ 14400u
#define BAUDRATE_19200_ 19200u
#define BAUDRATE_38400_ 38400u
#define BAUDRATE_57600_ 57600u
#define BAUDRATE_115200_ 115200u
#define BAUDRATE_128000_ 128000u
#define BAUDRATE_256000_ 256000u

#define BDH_VALUES 6u
#if BUS_CLOCK == 20000000L
#define BRFA_0_      0u
#define BDH_300_     16u
#define BDL_300_     6u
#define BDH_600_     8u
#define BDL_600_     35u
#define BDH_1200_    4u
#define BDL_1200_    65u
#define BDH_2400_    2u
#define BDL_2400_    9u
#define BDH_4800_    1u
#define BDL_4800_    4u
#define BDH_0_       0u
#define BDL_9600_    130u
#define BRFA_14400_  26u
#define BDL_14400_   87u
#define BRFA_19200_  4u
#define BDL_19200_   65u
#define BRFA_38400_  18u
#define BDL_38400_   32u
#define BRFA_57600_  23u
#define BDL_57600_   21u
#define BRFA_115200_ 27u
#define BDL_115200_  10u
#define BRFA_128000_ 25u
#define BDL_128000_  9u
#define BRFA_256000_ 28u
#define BDL_256000_  4u

/* @Madursk: Here should be defined YOUR calculated values*/
/*#else
#define BRFA_0_      0u
#define BDH_300_     16u
#define BDL_300_     6u
#define BDH_600_     8u
#define BDH_1200_    4u
#define BDL_1200_    65u
#define BDH_2400_    2u
#define BDL_2400_    9u
#define BDH_4800_    1u
#define BDL_4800_    4u
#define BDH_0_       0u
#define BDL_9600_    130u
#define BRFA_14400_  26u
#define BDL_14400_   87u
#define BRFA_19200_  4u
#define BDL_19200_   65u
#define BRFA_38400_  18u
#define BDL_38400_   32u
#define BRFA_57600_  23u
#define BDL_57600_   21u
#define BRFA_115200_ 27u
#define BDL_115200_  10u
#define BRFA_128000_ 25u
#define BDL_128000_  9u
#define BRFA_256000_ 28u
#define BDL_256000_  4u
*/
#endif

#define U8_UART_RX_BUFFER_LENGTH 40u
#define U8_UART3_IRQ_HANDLER 5u
#define U8_UART3_ERROR_HANDLER 6u
#define U8_UART3_MUX_MODE 3u
#define UART_END_TRANSMISSION 13u /*You can change this to the end you desire */
#define UART_END_RECEPTION 13u

/********************************************************************/

/***************STRUCTURES,UNIONS,ENUMS******************************/
 typedef struct 
 {
    uint8_t TXMODE     :1;
    uint8_t RXMODE     :1;
    uint8_t OVERRUNERR :1;
    uint8_t NOISEERR   :1;
    uint8_t FRAMINERR  :1;
    uint8_t PARITYERR  :1;
   
 }UART_Status_st;

typedef enum
{
  FALSE,
  TRUE,
}Status_en;
typedef enum
{
  INACTIVE,
  UART0,
  UART1,
  UART2,
  UART3,
  UART4

}UART_Channels_en;

typedef struct
{
  UART_Channels_en aeUART_ActiveChannels[UART_HW_UNITS];
  uint32_t au32UART_Channels_Baudrate[UART_HW_UNITS];

}UART_ModuleConfiguration_st;

typedef  UART_ModuleConfiguration_st* UART_ModuleConfiguration_stPtr;
/*****************************************************************/

/*************************PROTOTYPES*****************************/
Status_en vfnUARTInit(UART_ModuleConfiguration_stPtr UART_CfgStructPtr);
void vfnUARTBaudrate(UART_ModuleConfiguration_stPtr UART_CfgStructPtr);
void vfnUARTSend();
void vfnUARTInterruptEnable();
Status_en efnUARTWrite(const char_t lcTxBuffer[]);
Status_en efnUARTRead(char_t* lcRxBufferPointer, uint8_t lu8RxBufferSize);
uint8_t u8fnBDHSearch(uint32_t lu32Baudrate);
uint8_t u8fnBRFASearch(uint32_t lu32Baudrate);
uint8_t u8fnBDLSearch(uint32_t lu32Baudrate);
/**************************************************************/

#endif /* UARTDRIVER_H_ */
