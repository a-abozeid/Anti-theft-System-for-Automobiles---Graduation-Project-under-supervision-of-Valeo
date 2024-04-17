 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: SPI.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - SPI Driver
 *
 * Author: Mourad Eldin Nash'at
 ******************************************************************************/


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "Spi_Regs.h"
#include "Spi.h"

#if (SPI_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif



/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

STATIC const Spi_ConfigModule * Spi_ModulePtr = NULL_PTR;



/*******************************************************************************
 *                       	  Functions Definitions                            *
 *******************************************************************************/

/************************************************************************************
* Service Name: Spi_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service for SPI initialization.
************************************************************************************/
void Spi_Init(const Spi_ConfigType * ConfigPtr)
{
    /* loop on the configuration structure array */

    /* Loop Counter */
    uint8 spi_counter = 0;
    
    /* Pointer holds The SPI base Address */
    volatile uint32 * spiBaseAddressPtr = NULL_PTR;
    
    /* variable to hold The Delay Value for the clock */
    volatile unsigned long delay = 0;

    Spi_ModulePtr = ConfigPtr -> SSI_Modules;

    for(spi_counter = 0; spi_counter < SSI_MODULE_NUMBERS; spi_counter++)
    {
        /* Skip the configuration if it is a disabled (NOT USED) UART */
        if (Spi_ModulePtr[spi_counter].statusMode == SSI_OFF) {
            continue;
        }

        /* Enable the clock for the SSI Registers */
        SET_BIT(SSI_RCGC_REG , spi_counter);
        delay = SSI_RCGC_REG; /* Give time for the clock to start */
        delay = SSI_RCGC_REG; /* Give time for the clock to start */

        /* Check which Module is being used */
        switch (spi_counter)
        {
        /* SSI0 Module */    
        case SSI0_MODULE_NUMBER:
            spiBaseAddressPtr = (volatile uint32 *)SSI0_BASE_ADDRESS; 
            CLEAR_BIT(SSI0_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI1 Module */      
        case SSI1_MODULE_NUMBER:
            spiBaseAddressPtr = (volatile uint32 *)SSI1_BASE_ADDRESS;
            CLEAR_BIT(SSI1_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI2 Module */      
        case SSI2_MODULE_NUMBER:
            spiBaseAddressPtr = (volatile uint32 *)SSI2_BASE_ADDRESS;
            CLEAR_BIT(SSI2_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI3 Module */  
        case SSI3_MODULE_NUMBER:
            spiBaseAddressPtr = (volatile uint32 *)SSI3_BASE_ADDRESS;
            CLEAR_BIT(SSI3_CONTROL_REG1 , SSI_SSE_BIT);
            break;        
        default:
            break;
        }


        switch (Spi_ModulePtr[spi_counter].masterSlaveMode)
        {
        case MASTER_MODE:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG1_OFFSET) = 0x0000000;
            break;
        case SLAVE_MODE_OUTPUT_ENABLED:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG1_OFFSET) = 0x00000004;
            break;    
        case SLAVE_MODE_OUTPUT_DISABLED:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG1_OFFSET) = 0x0000000C;
            break;
        default:
            break;
        }


        switch (Spi_ModulePtr[spi_counter].clockConfiguration)
        {
        case SYTSTEM_CLOCK:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CLOCK_CONFIGURATION_OFFSET) &= 0x0000000;
            break;
        case PIOSC:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CLOCK_CONFIGURATION_OFFSET) |= 0x00000005;
            break;
        }

        /* SSInClk = SysClk / (CPSDVSR * (1 + SCR)) */
        *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_PRESCALE_REG_OFFSET) = Spi_ModulePtr[spi_counter].CPSDVSRRegValue;
        
        *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= ((Spi_ModulePtr[spi_counter].SCRRegValue)<<8);

        


        switch (Spi_ModulePtr[spi_counter].frameFormatSelect)
        {
        case FREESCALE_SPI_FRAME_FORMAT:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) &= ~(1 << 4) & ~(1 << 5);
            break;
        case TI_SS_FRAME_FORMAT:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= (1 << 4);
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) &= ~(1 << 5);
            break;
        case MICROWIRE_FRAME_FORAMT:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) &= ~(1 << 4);
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= (1 << 5);
            break;
        default:
            break;
        }


        /* Configuring The SSI Clock Phase Detection in case of Free Scale SPI Format Only */
        if(Spi_ModulePtr[spi_counter].frameFormatSelect == FREESCALE_SPI_FRAME_FORMAT)
        {
            switch (Spi_ModulePtr[spi_counter].clockPhase)
            {
            case FIRST_EDGE_TRANSITION:
                *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) &= ~(1 << 7);
                break;
            case SECOND_EDGE_TRANSITION:
                *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= (1 << 7);
                break;
            }
        }


        /* Configuring The SSI Clock Polarity */
        switch (Spi_ModulePtr[spi_counter].clockPolarity)
        {
        case STEADY_STATE_LOW:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) &= ~(1 << 6);
            break;
        case STEADY_STATE_HIGH:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= (1 << 6);
            break;
        }


        switch (Spi_ModulePtr[spi_counter].dataSize)
        {
        case FOUR_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000003;
            break;
        case FIVE_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000004;
            break;
        case SIX_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000005;
            break;
        case SEVEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000006;
            break;
        case EIGHT_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000007;
            break;
        case NINE_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000008;
            break;
        case TEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x00000009;
            break;
        case ELEVEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000A;
            break;
        case TWELVE_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000B;
            break;
        case THIRTEEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000C;
            break;
        case FOURTEEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000D;
            break;
        case FIFTEEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000E;
            break;
        case SIXTEEN_BIT_DATA:
            *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_CONTROL_REG0_OFFSET) |= 0x0000000F;
            break;
        default:
            break;
        }


        /* Enable The SSI by setting the SSE bit in the SSICR1 register. */
        switch (spi_counter)
        {
        /* SSI0 Module */    
        case SSI0_MODULE_NUMBER:
            SET_BIT(SSI0_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI1 Module */      
        case SSI1_MODULE_NUMBER:
            SET_BIT(SSI1_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI2 Module */      
        case SSI2_MODULE_NUMBER:
            SET_BIT(SSI2_CONTROL_REG1 , SSI_SSE_BIT);
            break;
        /* SSI3 Module */  
        case SSI3_MODULE_NUMBER:
            SET_BIT(SSI3_CONTROL_REG1 , SSI_SSE_BIT);
            break;        
        default:
            break;
        }
    }

}



uint8 SPI_SendReceiveByte(SSI_ModuleNumber moduleNumber,uint8 data)
{
    /* Pointer holds The SPI base Address */
    volatile uint32* spiBaseAddressPtr = NULL_PTR;

    /* variable to hold The Delay Value for the clock */
    volatile unsigned long delay = 0;

    /* Check which Module is being used */
    switch (moduleNumber)
    {
        /* SSI0 Module */
    case SSI0_MODULE_NUMBER:
        spiBaseAddressPtr = (volatile uint32*)SSI0_BASE_ADDRESS;
        break;
        /* SSI1 Module */
    case SSI1_MODULE_NUMBER:
        spiBaseAddressPtr = (volatile uint32*)SSI1_BASE_ADDRESS;
        break;
        /* SSI2 Module */
    case SSI2_MODULE_NUMBER:
        spiBaseAddressPtr = (volatile uint32*)SSI2_BASE_ADDRESS;
        break;
        /* SSI3 Module */
    case SSI3_MODULE_NUMBER:
        spiBaseAddressPtr = (volatile uint32*)SSI3_BASE_ADDRESS;
        break;
    default:
        break;
    }


    while(((*(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_STATUS_REG_OFFSET)) & SSI_TNF_MASK) == 0);
	

	*(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_DATA_REG_OFFSET) = data;

    while((*(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_STATUS_REG_OFFSET)) & SSI_BSY_MASK);     /* wait until transmit complete */
	
    return *(volatile uint32 *)((volatile uint8 *)spiBaseAddressPtr + SSI_DATA_REG_OFFSET);
}