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
#define UART_HW_UNITS_LFIFOS 2u
#define UART_HW_ISO7816_UNITS 1u


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
#define BDH_300_     17u
#define BDL_300_     11u
#define BDH_600_     8u
#define BDL_600_     139u
#define BRFA_600_     16u
#define BDH_1200_    4u
#define BDL_1200_    69u
#define BRFA_1200_   24u
#define BDH_2400_    2u
#define BDL_2400_    34u
#define BRFA_2400_   28u
#define BDH_4800_    1u
#define BDL_4800_    17u
#define BRFA_4800_   14u
#define BDH_0_       0u
#define BDH_9600_    8u
#define BDL_9600_    139u
#define BRFA_9600_   16
#define BRFA_14400_  5u
#define BDL_14400_   91u
#define BRFA_19200_  12u
#define BDL_19200_   68u
#define BRFA_38400_  6u
#define BDL_38400_   34u
#define BRFA_57600_  25u
#define BDL_57600_   22u
#define BRFA_115200_ 13u
#define BDL_115200_  11u
#define BRFA_128000_ 8u
#define BDL_128000_  10u
#define BRFA_256000_ 4u
#define BDL_256000_  5u

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
  UART_INACTIVE,
  UART0,
  UART1,
  UART2,
  UART3,
  UART4,
  UART_ACTIVE

}UART_Channels_en;

typedef enum 
{
  ONE_DATAWORD,
  FOUR_DATAWORDS,
  EIGHT_DATAWORDS

}UART_Buffer_Datawords_en;

typedef enum
{
  HANDSHAKE_INACTIVE,
  RTS_CTS
}UART_Handshake_en;

typedef enum
{
  IRDA_INACTIVE,
  IRDA_ACTIVE

}UART_IRDA_en;

typedef enum
{
  ISO7816_INACTIVE,
  ISO7816_ACTIVE

}UART_ISO7816_en;

typedef enum
{
  PARITY_INACTIVE,
  EVEN,
  ODD

}UART_Parity_en;

typedef enum
{
  COMM_MODE_INACTIVE,
  INTERRUPTS,
  DMA,
  POLLING
}UART_Communication_Mode_en;

typedef enum
{
  UART_UNINITIALIZED,
  UART_INITIALIZED,
  UART_LFIFOS_CFG_MISMTCH,
  UART_BAUDRATE_MISMTCH,
  UART_FIFOS_CFG_MISMTCH,
  UART_PARITY_CFG_MISMTCH,
  UART_HANDSHAKE_CFG_MISMTCH,
  UART_DATAWAORDS_CFG_MISMTCH,
  UART_IRDA_CFG_MISMTCH,
  UART_ISO7816_CFG_MISMTCH

}UART_Status_en;
typedef struct
{ 

  UART_Channels_en aeUART_ActiveChannels[UART_HW_UNITS];
  uint32_t au32UART_Channels_Baudrate[UART_HW_UNITS];
  UART_Channels_en aeUART_ActiveChannels_LFIFOS[UART_HW_UNITS_LFIFOS];
  UART_Buffer_Datawords_en aeUART_Channels_FIFOS[UART_HW_UNITS];
  UART_Parity_en aeUART_Channel_Parity[UART_HW_UNITS];
  UART_Handshake_en aeUART_Channels_Handshake[UART_HW_UNITS];
  UART_IRDA_en aeUART_Channels_IRDAs[UART_HW_UNITS];
#if UART_HW_ISO7816_UNITS == 1
  UART_ISO7816_en eUART_Chanel_ISO7816;
#elif UART_HW_ISO7816_UNITS > 1 
  UART_ISO7816_en aeUART_Chanel_ISO7816[UART_HW_ISO7816_UNITS];
#else

#endif
 UART_Communication_Mode_en aeUART_Channels_Comm_Mode[UART_HW_UNITS];

}UART_ModuleConfiguration_st;

typedef  UART_ModuleConfiguration_st* UART_ModuleConfiguration_stPtr;
/*****************************************************************/

/*************************PROTOTYPES*****************************/
UART_Status_en* vfnUARTInit(UART_ModuleConfiguration_stPtr UART_CfgStructPtr);
void vfnUARTBuffersCfg(UART_ModuleConfiguration_stPtr UART_CfgStructPtr);
void vfnUARTBaudrate(UART_ModuleConfiguration_stPtr UART_CfgStructPtr);
void vfnUARTSend();
void vfnUARTInterruptEnable();
std_ReturnType u8fnUARTWrite(char_t lcTxBuffer[]);
std_ReturnType u8fnUARTRead(char_t lcRxBuffer[], uint8_t lu8RxBufferSize);
uint8_t u8fnBDHSearch(uint32_t lu32Baudrate);
uint8_t u8fnBRFASearch(uint32_t lu32Baudrate);
uint8_t u8fnBDLSearch(uint32_t lu32Baudrate);
/**************************************************************/

#endif /* UARTDRIVER_H_ */
