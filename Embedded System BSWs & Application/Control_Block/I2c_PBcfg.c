 /******************************************************************************
 *
 * Module: I2c
 *
 * File Name: I2c_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - I2c Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "I2c.h"

const I2c_ConfigType I2c_Confiuration = {
    /* I2C 0 Module */
    I2C_DISABLED, I2C_MASTER_MODE, I2C_STANDARD_SPEED_MODE,
    
    /* I2C 1 Module */
    I2C_DISABLED, I2C_MASTER_MODE, I2C_STANDARD_SPEED_MODE,
    
    /* I2C 2 Module */
    I2C_ENABLED, I2C_MASTER_MODE, I2C_STANDARD_SPEED_MODE,
    
    /* I2C 3 Module */
    I2C_DISABLED, I2C_MASTER_MODE, I2C_STANDARD_SPEED_MODE,

};