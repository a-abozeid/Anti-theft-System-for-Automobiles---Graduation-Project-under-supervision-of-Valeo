 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detection */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* Symbolic names for port numbers */
#define PORT_A                               (uint8)0 /* PORT A */
#define PORT_B                               (uint8)1 /* PORT B */
#define PORT_C                               (uint8)2 /* PORT C */
#define PORT_D                               (uint8)3 /* PORT D */
#define PORT_E                               (uint8)4 /* PORT E */
#define PORT_F                               (uint8)5 /* PORT F */

/* Symbolic names for port pins*/
/* PORT A pins */
#define PORT_A_PIN_0                         (uint8)0
#define PORT_A_PIN_1                         (uint8)1
#define PORT_A_PIN_2                         (uint8)2
#define PORT_A_PIN_3                         (uint8)3
#define PORT_A_PIN_4                         (uint8)4
#define PORT_A_PIN_5                         (uint8)5
#define PORT_A_PIN_6                         (uint8)6
#define PORT_A_PIN_7                         (uint8)7

/* PORT B pins */
#define PORT_B_PIN_0                         (uint8)0
#define PORT_B_PIN_1                         (uint8)1
#define PORT_B_PIN_2                         (uint8)2
#define PORT_B_PIN_3                         (uint8)3
#define PORT_B_PIN_4                         (uint8)4
#define PORT_B_PIN_5                         (uint8)5
#define PORT_B_PIN_6                         (uint8)6
#define PORT_B_PIN_7                         (uint8)7

/* PORT C pins */
#define PORT_C_PIN_0                         (uint8)0
#define PORT_C_PIN_1                         (uint8)1
#define PORT_C_PIN_2                         (uint8)2
#define PORT_C_PIN_3                         (uint8)3
#define PORT_C_PIN_4                         (uint8)4
#define PORT_C_PIN_5                         (uint8)5
#define PORT_C_PIN_6                         (uint8)6
#define PORT_C_PIN_7                         (uint8)7

/* PORT D pins */
#define PORT_D_PIN_0                         (uint8)0
#define PORT_D_PIN_1                         (uint8)1
#define PORT_D_PIN_2                         (uint8)2
#define PORT_D_PIN_3                         (uint8)3
#define PORT_D_PIN_4                         (uint8)4
#define PORT_D_PIN_5                         (uint8)5
#define PORT_D_PIN_6                         (uint8)6
#define PORT_D_PIN_7                         (uint8)7

/* PORT E pins */
#define PORT_E_PIN_0                         (uint8)0
#define PORT_E_PIN_1                         (uint8)1
#define PORT_E_PIN_2                         (uint8)2
#define PORT_E_PIN_3                         (uint8)3
#define PORT_E_PIN_4                         (uint8)4
#define PORT_E_PIN_5                         (uint8)5

/* PORT F pins */
#define PORT_F_PIN_0                         (uint8)0
#define PORT_F_PIN_1                         (uint8)1
#define PORT_F_PIN_2                         (uint8)2
#define PORT_F_PIN_3                         (uint8)3
#define PORT_F_PIN_4                         (uint8)4

#endif /* PORT_CFG_H */
