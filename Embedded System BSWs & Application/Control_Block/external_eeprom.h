 /******************************************************************************
 *
 * Module: external_eeprom
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for external_eeprom 
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPROM_H

/*******************************************************************************
 *                            Include Files                                    *
 *******************************************************************************/
#include "I2c.h"
#include "Std_Types.h"
#include "external_eeprom_cfg.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#ifndef ERROR
#define ERROR 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H*/