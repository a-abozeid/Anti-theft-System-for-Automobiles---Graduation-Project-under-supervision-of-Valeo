 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: Spi_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - SPI Driver Registers
 *
 * Author: Mourad Eldin Nash'at
 ******************************************************************************/


#ifndef SPI_REGS_H
#define SPI_REGS_H


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "Std_Types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* TM4123GH6PM SSI Modules Base Addresses */
#define SSI0_BASE_ADDRESS           (0x40008000) /* SSI0 Base Address */
#define SSI1_BASE_ADDRESS           (0x40009000) /* SSI1 Base Address */
#define SSI2_BASE_ADDRESS           (0x4000A000) /* SSI2 Base Address */
#define SSI3_BASE_ADDRESS           (0x4000B000) /* SSI3 Base Address */


/* SSI0 Control Registers */
#define SSI0_CONTROL_REG0           *((volatile uint32 *)(0x40008000))
#define SSI0_CONTROL_REG1           *((volatile uint32 *)(0x40008004))
#define SSI0_DATA_REG               *((volatile uint32 *)(0x40008008))
#define SSI0_PRESCALE               *((volatile uint32 *)(0x40008010))
#define SSI0_DMA_CONTROL            *((volatile uint32 *)(0x40008024))
#define SSI_CLOCK_CONFIGURATION     *((volatile uint32 *)(0x40008FC8))

/* SSI1 Control Registers */
#define SSI1_CONTROL_REG0           *((volatile uint32 *)(0x40009000)) 
#define SSI1_CONTROL_REG1           *((volatile uint32 *)(0x40009004))
#define SSI1_DATA_REG               *((volatile uint32 *)(0x40009008))
#define SSI1_PRESCALE               *((volatile uint32 *)(0x40009010))
#define SSI1_DMA_CONTROL            *((volatile uint32 *)(0x40009024))


/* SSI2 Control Registers */
#define SSI2_CONTROL_REG0           *((volatile uint32 *)(0x4000A000))
#define SSI2_CONTROL_REG1           *((volatile uint32 *)(0x4000A004))
#define SSI2_DATA_REG               *((volatile uint32 *)(0x4000A008))
#define SSI2_PRESCALE               *((volatile uint32 *)(0x4000A010))
#define SSI2_DMA_CONTROL            *((volatile uint32 *)(0x4000A024))


/* SSI3 Control Registers */
#define SSI3_CONTROL_REG0           *((volatile uint32 *)(0x4000B000))
#define SSI3_CONTROL_REG1           *((volatile uint32 *)(0x4000B004))
#define SSI3_DATA_REG               *((volatile uint32 *)(0x4000B008))
#define SSI3_PRESCALE               *((volatile uint32 *)(0x4000B010))
#define SSI3_DMA_CONTROL            *((volatile uint32 *)(0x4000B024))



/* SSI Control Regsiters Offsets */
#define SSI_RCG                            (0x61C) 
#define SSI_CONTROL_REG0_OFFSET            (0x000)
#define SSI_CONTROL_REG1_OFFSET            (0x004)
#define SSI_DATA_REG_OFFSET                (0X008)
#define SSI_PRESCALE_REG_OFFSET            (0x010)
#define SSI_DMA_CONTROL_REG_OFFSET         (0x024)
#define SSI_CLOCK_CONFIGURATION_OFFSET     (0xFC8)
#define SSI_STATUS_REG_OFFSET              (0x00C)

/* SSI Run Mode Clock Gating Control Register to enable clock for the SSI modules */
#define SSI_RCGC_REG    *((volatile uint32 *)(0x400FE61C))


#endif /* SPI_REGS_H */
