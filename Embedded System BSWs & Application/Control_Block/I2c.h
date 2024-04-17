 /******************************************************************************
 *
 * Module: I2c
 *
 * File Name: I2c.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - I2c Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/
#ifndef I2C_H
#define I2C_H

/*******************************************************************************
 *                            Include Files                                    *
 *******************************************************************************/
/* Include I2C registers */
#include "I2c_Regs.h"

/* Include Standard Types */
#include "Std_Types.h"

/* Include Common Macros */
#include "Common_Macros.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Number of I2C Modules in the tiva c */
#define NUMBER_OF_I2C_MODULES (4U)



#define I2C_STANDARD_MODE_FREQUENCY (100000U)
#define SCL_LP (6U)
#define SCL_HP (4U)

typedef enum {
    I2C_MODULE_0,
    I2C_MODULE_1,
    I2C_MODULE_2,
    I2C_MODULE_3
} I2c_ModuleNumber;

typedef enum {
    I2C_DISABLED, I2C_ENABLED
} I2c_StatusMode;

typedef enum {
    I2C_STANDARD_SPEED_MODE,
    I2C_FAST_SPEED_MODE,
    I2C_FAST_SPEED_PLUS_MODE,
    I2C_HIGH_SPEED_MODE
} I2c_SpeedMode;

typedef enum {
    I2C_MASTER_MODE,
    I2C_SLAVE_MODE
} I2c_MasterSlaveMode;

typedef struct {
    I2c_StatusMode i2c_status_mode;
    I2c_MasterSlaveMode i2c_master_slave_mode;
    I2c_SpeedMode i2c_speed_mode;
} I2c_ConfigModule;

typedef struct {
    I2c_ConfigModule I2cModules[NUMBER_OF_I2C_MODULES];
} I2c_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function prototype for I2C init Function */
void I2c_Init(const I2c_ConfigType * ConfigPtr);
void I2c_Init(const I2c_ConfigType * ConfigPtr);
uint8 I2c_WriteByte(I2c_ModuleNumber i2cModuleNumber,uint8 slaveAddress, uint8 slaveMemoryAddress, uint8 byte);
uint8 I2c_ReadByte(I2c_ModuleNumber i2cModuleNumber,uint8 slaveAddress, uint8 slaveMemoryAddress,uint8 * data);



/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by I2c and other modules */
extern const I2c_ConfigType I2c_Confiuration;


#endif