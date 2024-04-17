 /******************************************************************************
 *
 * Module: I2c
 *
 * File Name: I2c.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - I2c Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "I2c.h"
#include "I2c_Regs.h"

#ifndef F_CPU
#define F_CPU (16000000U)
#endif

STATIC const I2c_ConfigModule * I2c_ModulePtr = NULL_PTR;
STATIC int I2C_wait_till_done(uint32 * i2cModuleBasePtr);

/************************************************************************************
* Service Name: I2c_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the I2c module.

*** Note ***: The only supported modes at the moment are STANDARD speed mode and MASTER mode only. 
************************************************************************************/
void I2c_Init(const I2c_ConfigType * ConfigPtr)
{
    /* Variables Declrations */
    uint8 i2cCounter = 0;
    uint32 masterTimerPerioidValue = 0;
    volatile unsigned long delay = 0;
    volatile uint32 * i2cModuleBasePtr = NULL_PTR;

    I2c_ModulePtr = (ConfigPtr->I2cModules);

    /* Loop through the four I2C Modules */
    for(i2cCounter = 0; i2cCounter < NUMBER_OF_I2C_MODULES; i2cCounter++){
        if(I2c_ModulePtr[i2cCounter].i2c_status_mode == I2C_DISABLED){
            /* I2C Module is not used so skip it */
            continue;
        }

        switch (i2cCounter)
        {
        case I2C_MODULE_0:
            i2cModuleBasePtr = (volatile uint32 *)I2C_0_BASE_ADDRESS;
            break;
        case I2C_MODULE_1:
            i2cModuleBasePtr = (volatile uint32 *)I2C_1_BASE_ADDRESS;
            break;
        case I2C_MODULE_2:
            i2cModuleBasePtr = (volatile uint32 *)I2C_2_BASE_ADDRESS;
            break;
        case I2C_MODULE_3:
            i2cModuleBasePtr = (volatile uint32 *)I2C_3_BASE_ADDRESS;
            break;
        default:
            break;
        }

        /* Enable the clock for the i2c module */
        SET_BIT(I2C_RCGC_REG, i2cCounter);
        delay = I2C_RCGC_REG;
        delay = I2C_RCGC_REG;
        
        if( (I2c_ModulePtr[i2cCounter].i2c_master_slave_mode) == I2C_MASTER_MODE){
            /* Master Mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONFIG_REG_OFFSET), I2C_MFE_BIT);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONFIG_REG_OFFSET), I2C_SFE_BIT);
        } else {
            /* Slave Mode */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONFIG_REG_OFFSET), I2C_SFE_BIT);
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONFIG_REG_OFFSET), I2C_MFE_BIT);
        }
        
        /* Set the frequency of I2C */
        /* (1 + TIME_PERIOD ) = SYS_CLK /(2 * ( SCL_LP + SCL_HP ) * I2C_CLK_Freq ) */
        switch (I2c_ModulePtr[i2cCounter].i2c_speed_mode)
        {
        case I2C_STANDARD_SPEED_MODE:
            masterTimerPerioidValue = (((1.0f/I2C_STANDARD_MODE_FREQUENCY) / ( (SCL_LP+SCL_HP) * (1.0f/ F_CPU) )) / 2 ) - 1;
            *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_TIMER_PERIOD_REG_OFFSET) = masterTimerPerioidValue;
            break;
        case I2C_FAST_SPEED_MODE:
            break;
        case I2C_FAST_SPEED_PLUS_MODE:
            break;
        case I2C_HIGH_SPEED_MODE:
            break;
        default:
            break;
        }
    }
}

/************************************************************************************
* Service Name: I2c_WriteByte
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): i2cModuleNumber - number of the i2c module used for trasmission
                   slaveAddress - slave address of the device to communicate with
                   slaveMemoryAddress - address of the memory location to be accessed
                   byte - the actualy byte to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: uint8 error - error code, 0 if no errors
* Description: Function to write a byte through i2c.
************************************************************************************/
uint8 I2c_WriteByte(I2c_ModuleNumber i2cModuleNumber,uint8 slaveAddress, uint8 slaveMemoryAddress, uint8 byte){
    volatile uint32 * i2cModuleBasePtr = NULL_PTR;
    uint8 error = 0;

    /* Get the base address of the used i2c module */
    switch (i2cModuleNumber)
    {
    case I2C_MODULE_0:
        i2cModuleBasePtr = (volatile uint32 *)I2C_0_BASE_ADDRESS;
        break;
    case I2C_MODULE_1:
        i2cModuleBasePtr = (volatile uint32 *)I2C_1_BASE_ADDRESS;
        break;
    case I2C_MODULE_2:
        i2cModuleBasePtr = (volatile uint32 *)I2C_2_BASE_ADDRESS;
        break;
    case I2C_MODULE_3:
        i2cModuleBasePtr = (volatile uint32 *)I2C_3_BASE_ADDRESS;
        break;
    default:
        break;
    }
    
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_SLAVE_ADDRESS_REG_OFFSET) = slaveAddress;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_DATA_REG_OFFSET) = slaveMemoryAddress;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET) = 3;

    error = I2C_wait_till_done((uint32 *)i2cModuleBasePtr);

    if(error) return error;

    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_DATA_REG_OFFSET) = byte;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET) = 5;

    error = I2C_wait_till_done((uint32 *)i2cModuleBasePtr);

    if(error) return error;
    
    return 1;
}

uint8 I2c_ReadByte(I2c_ModuleNumber i2cModuleNumber,uint8 slaveAddress, uint8 slaveMemoryAddress,uint8 * data){
    volatile uint32 * i2cModuleBasePtr = NULL_PTR;
    uint8 error = 0;
    switch (i2cModuleNumber)
    {
    case I2C_MODULE_0:
        i2cModuleBasePtr = (volatile uint32 *)I2C_0_BASE_ADDRESS;
        break;
    case I2C_MODULE_1:
        i2cModuleBasePtr = (volatile uint32 *)I2C_1_BASE_ADDRESS;
        break;
    case I2C_MODULE_2:
        i2cModuleBasePtr = (volatile uint32 *)I2C_2_BASE_ADDRESS;
        break;
    case I2C_MODULE_3:
        i2cModuleBasePtr = (volatile uint32 *)I2C_3_BASE_ADDRESS;
        break;
    default:
        break;
    } 

    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_SLAVE_ADDRESS_REG_OFFSET) = slaveAddress;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_DATA_REG_OFFSET) = (uint8)slaveMemoryAddress;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET) = 3;
    
    error = I2C_wait_till_done((uint32 *)i2cModuleBasePtr);
    if(error) return error;
    
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_SLAVE_ADDRESS_REG_OFFSET) = slaveAddress + 1;
    *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET) = 7;

    error = I2C_wait_till_done((uint32 *)i2cModuleBasePtr);
    if(error) return error;

    *data = *(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_DATA_REG_OFFSET);

    /* wait until bus is not busy */
    while((*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET)) & 0x40);    
    return 1;       /* no error */
}
STATIC int I2C_wait_till_done(uint32 * i2cModuleBasePtr)
{
    /* wait until I2C master is not busy */
    while((*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET)) & 1);
    /* return I2C error code, 0 if no error */
    return (*(volatile uint32 *)((volatile uint8 *)i2cModuleBasePtr + I2C_MASTER_CONTROL_STATUS_REG_OFFSET)) & 0xE; 
}