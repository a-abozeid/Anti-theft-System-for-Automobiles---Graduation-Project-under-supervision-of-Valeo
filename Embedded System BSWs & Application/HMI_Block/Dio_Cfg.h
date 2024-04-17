 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/* Include Dio_Regs to get PORT_IDs definitions */
#include "Dio_Regs.h"
/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/****************** Dio Channels Settings ******************/

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (12U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
//#define DioConf_LED1_CHANNEL_ID_INDEX        ((uint8)0x00)
//#define DioConf_SW1_CHANNEL_ID_INDEX         ((uint8)0x01)

/* DIO Configured Port ID's  */
//#define DioConf_LED1_PORT_NUM                ((Dio_PortType)GPIO_PORTF_ID) /* PORTF */
//#define DioConf_SW1_PORT_NUM                 ((Dio_PortType)GPIO_PORTF_ID) /* PORTF */

/* DIO Configured Channel ID's */
//#define DioConf_LED1_CHANNEL_NUM             ((Dio_ChannelType)GPIO_PF1) /* Pin 1 in PORTF */
//#define DioConf_SW1_CHANNEL_NUM              ((Dio_ChannelType)GPIO_PF4) /* Pin 4 in PORTF */


/****************** Dio Group Channels Settings ******************/

/* Number of the configured group channels */
#define DIO_CONFIGURED_GROUP_CHANNELS        (1U) 
#define DioConf_LCD_GRP_INDEX               ((uint8)0)

/* Channel Index in the array of structures of configured group channels in Dio_PBcfg.c */
#define DioConf_LCD_GRP_PTR                 (((&Dio_Configuration)->GroupChannels)+DioConf_LCD_GRP_INDEX)

/* DIO Configured group channel Port ID's  */

#define DioConf_LCD_GRP_PORT_NUM                 ((Dio_PortType)GPIO_PORTC_ID) /* PORTF */

/* DIO Configured group channel MASK */


#define DioConf_LCD_GRP_MASK                    ((uint8)0xF0) /* 4 Pins at the left */

/* DIO Configured group channel offset */
#define DioConf_LCD_GRP_OFFSET                  ((uint8)4)

/* DIO Configuired group channel offset */







/* Dio Configuration for LCD */
#define DioConf_LCD_PORT_NUM GPIO_PORTC_ID

#define DioConf_LCD_RS_CHANNEL_ID_INDEX ((uint8)0)
#define DioConf_LCD_RW_CHANNEL_ID_INDEX ((uint8)1)
#define DioConf_LCD_EN_CHANNEL_ID_INDEX ((uint8)2)

#define DioConf_LCD_RS_PORT_NUM (GPIO_PORTA_ID)
#define DioConf_LCD_RW_PORT_NUM (GPIO_PORTA_ID)
#define DioConf_LCD_EN_PORT_NUM (GPIO_PORTA_ID)

#define DioConf_LCD_RS_CHANNEL_NUM (GPIO_PA5)
#define DioConf_LCD_RW_CHANNEL_NUM (GPIO_PA6)
#define DioConf_LCD_EN_CHANNEL_NUM (GPIO_PA7)

/* SPI Slave Select */
#define DioConf_SPI_SS_CHANNEL_ID_INDEX ((uint8)3)
#define DioConf_SPI_SS_PORT_NUM (GPIO_PORTF_ID)
#define DioConf_SPI_SS_CHANNEL_NUM (GPIO_PF4)


/* keypad */
#define DioConf_KEYPAD_BASE_CHANNEL_ID_INDEX 4
#define DioConf_KEPAD_ROW0_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_ROW1_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_ROW2_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_ROW3_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_COL0_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_COL1_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_COL2_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)
#define DioConf_KEPAD_COL3_PORT_NUM ((Dio_PortType)GPIO_PORTB_ID)

#define DioConf_KEYPAD_ROW0_CHANNEL_NUM ((uint8) 0)
#define DioConf_KEYPAD_ROW1_CHANNEL_NUM ((uint8) 1)
#define DioConf_KEYPAD_ROW2_CHANNEL_NUM ((uint8) 2)
#define DioConf_KEYPAD_ROW3_CHANNEL_NUM ((uint8) 3)
#define DioConf_KEYPAD_COL0_CHANNEL_NUM ((uint8) 4)
#define DioConf_KEYPAD_COL1_CHANNEL_NUM ((uint8) 5)
#define DioConf_KEYPAD_COL2_CHANNEL_NUM ((uint8) 6)
#define DioConf_KEYPAD_COL3_CHANNEL_NUM ((uint8) 7)

#endif /* DIO_CFG_H */
