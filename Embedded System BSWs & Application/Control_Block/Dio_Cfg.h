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
#define DIO_CONFIGURED_CHANNLES              (3U)

/* Channel Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LED1_CHANNEL_ID_INDEX        ((uint8)0x00)
#define DioConf_LED2_CHANNEL_ID_INDEX        ((uint8)0x01)
#define DioConf_SW1_CHANNEL_ID_INDEX         ((uint8)0x02)



/* DIO Configured Port ID's  */
#define DioConf_LED1_PORT_NUM                ((Dio_PortType)GPIO_PORTA_ID) /* PORTF */
#define DioConf_LED2_PORT_NUM                ((Dio_PortType)GPIO_PORTA_ID) /* PORTF */
#define DioConf_SW1_PORT_NUM                 ((Dio_PortType)GPIO_PORTF_ID) /* PORTF */

/* DIO Configured Channel ID's */
#define DioConf_LED1_CHANNEL_NUM             ((Dio_ChannelType)GPIO_PA7) /* Pin 1 in PORTF */
#define DioConf_LED2_CHANNEL_NUM             ((Dio_ChannelType)GPIO_PA3) /* Pin 1 in PORTF */
#define DioConf_SW1_CHANNEL_NUM              ((Dio_ChannelType)GPIO_PF4) /* Pin 4 in PORTF */


/****************** Dio Group Channels Settings ******************/

/* Number of the configured group channels */
#define DIO_CONFIGURED_GROUP_CHANNELS        (0U) 

#endif /* DIO_CFG_H */
