 /******************************************************************************
 *
 * Module: external_eeprom
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for external_eeprom 
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/


/*******************************************************************************
 *                            Include Files                                    *
 *******************************************************************************/
#include "external_eeprom.h"


uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data){
    uint8 writeOperationStatus = 0;
    writeOperationStatus = I2c_WriteByte(EXTERNAL_EEPROM_I2C_MODULE, (uint8)(0xA0 | ((u16addr & 0x0700)>>7)), u16addr, u8data);
    if(writeOperationStatus == 0){
        return ERROR;
    } else return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data){
    uint8 readOperationStatus = 0;
    readOperationStatus = I2c_ReadByte(EXTERNAL_EEPROM_I2C_MODULE, (uint8)(0xA0 | ((u16addr & 0x0700)>>7)), u16addr, u8data);
    if(readOperationStatus == 0){
        return ERROR;
    } else return SUCCESS;
}
