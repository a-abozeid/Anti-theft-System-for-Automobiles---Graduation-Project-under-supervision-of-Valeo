 /******************************************************************************
 *
 * Module: I2c
 *
 * File Name: I2c_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - I2c Driver Registers
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/
#ifndef I2C_REGS_H
#define I2C_REGS_H

#define I2C_0_BASE_ADDRESS  (0x40020000) /* I2C 0 Base Address */
#define I2C_1_BASE_ADDRESS  (0x40021000) /* I2C 1 Base Address */
#define I2C_2_BASE_ADDRESS  (0x40022000) /* I2C 2 Base Address */
#define I2C_3_BASE_ADDRESS  (0x40023000) /* I2C 3 Base Address */


#define I2C_MASTER_CONFIG_REG_OFFSET            (0x020U) /* I2C MCR - Master Config Reg*/
#define I2C_MASTER_TIMER_PERIOD_REG_OFFSET      (0x00CU) /* I2C MTPR - Master Timer Perioid Reg */
#define I2C_MASTER_SLAVE_ADDRESS_REG_OFFSET     (0x000U) /* I2C MSA - Master Slave Address Reg */
#define I2C_MASTER_DATA_REG_OFFSET              (0x008U) /* I2C MDR - Master Data Reg */
#define I2C_MASTER_CONTROL_STATUS_REG_OFFSET    (0x004U) /* I2C MCS - Master Control Status Reg */

#define I2C_MFE_BIT (4U) /* I2C Master Function Enable Bit */
#define I2C_SFE_BIT (5U) /* I2C Slave Function Enable Bit */

/* I2C Run Mode Clock Gating Control Register to enable clock for the i2c modules */
#define I2C_RCGC_REG  (*((volatile uint32 *)0x400FE620))


#endif