#ifndef UART_H
#define UART_H

#include "Uart_Cfg.h"
#include "Std_Types.h"
#include "Uart_Regs.h"
#include "MCU_Config.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
#define NUMBER_OF_UART_MODULES       (8U)

#define UART_CLEAR_WORD_LENGTH_BITS_MASK  (0xFF9F)
#define UART_WORD_LENGTH_SHIFT_MASK       (5U)
#define UART_TXFF_MASK                    (0x20) /* Mask to check the Transmit Full Flag */
#define UART_RXEF_MASK                    (0x10) /* Mask to check the Receive Empty Flag */

typedef enum
{
    UART0_MODULE_NUMBER,
    UART1_MODULE_NUMBER,
    UART2_MODULE_NUMBER,
    UART3_MODULE_NUMBER,
    UART4_MODULE_NUMBER,
    UART5_MODULE_NUMBER,
    UART6_MODULE_NUMBER,
    UART7_MODULE_NUMBER,
} Uart_ModuleNumber;

typedef enum{
    UART_OFF,
    UART_ON
} Uart_StatusMode;

/* Enumeration to define the character size */
typedef enum
{
	UART_FIVE_BITS, UART_SIX_BITS, UART_SEVEN_BITS, UART_EIGHT_BITS
}Uart_DataBits;

/* Enumeration to define the parity type */
typedef enum
{
	UART_NO_PARITY, UART_ODD_PARITY, UART_EVEN_PARITY
}Uart_Parity;

/* Enumeration to define the number of stop bits */
typedef enum
{
	UART_ONE_STOP_BIT, UART_TWO_STOP_BIT
}Uart_StopBits;

typedef enum
{
    UART_POLLING, UART_INTERRUPT
}Uart_Mode;

typedef struct
{
    Uart_StatusMode statusMode;
	Uart_DataBits noDataBits;
	Uart_Parity parityType;
	Uart_StopBits noStopBits;   /*Number of stop bits*/
    Uart_Mode mode;
	uint32 baudRate;
}Uart_ConfigModule;

/* Data Structure required for initializing the UART Driver */
typedef struct UART_ConfigType
{
	const Uart_ConfigModule UARTModules[NUMBER_OF_UART_MODULES];
} Uart_ConfigType;



/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by I2c and other modules */
extern const Uart_ConfigType Uart_Configuration;

/**************************************DON'T KNOW WHAT THESE ARE*******************************/
extern uint8 flag;
extern uint8 RecDataBuffer;


/*Functions Prototypes*/


/********************************

 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void Uart_Init(const Uart_ConfigType * ConfigPtr);
/*
 * Description :
 * Functional responsible for send byte to another device.
 */
void Uart_SendByte(Uart_ModuleNumber uartModuleNumber ,const uint8 byteToSend);
/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 Uart_ReceiveByte(Uart_ModuleNumber uartModuleNumber);

#endif
