 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif



/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {
    /* PORT A pins*/
    PORT_A, PORT_A_PIN_0, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_1, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_2, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_3, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_4, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    /* LCD Control Pins*/
    PORT_A, PORT_A_PIN_5, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_6, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_A, PORT_A_PIN_7, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,

    /* PORT B pins*/
    /* Keypad Pins */
    PORT_B, PORT_B_PIN_0, PORT_PIN_IN, PORT_MODE_0, PULL_DOWN, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_1, PORT_PIN_IN, PORT_MODE_0, PULL_DOWN, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_2, PORT_PIN_IN, PORT_MODE_0, PULL_DOWN, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_3, PORT_PIN_IN, PORT_MODE_0, PULL_DOWN, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_4, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_5, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_6, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_B, PORT_B_PIN_7, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    
    /* PORT C pins*/
    PORT_C, PORT_C_PIN_0, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_1, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_2, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_3, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    /* LCD Data Pins */
    PORT_C, PORT_C_PIN_4, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_5, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_6, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_C, PORT_C_PIN_7, PORT_PIN_OUT, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    
    /* PORT D pins*/
    /* SPI Pins */
    PORT_D, PORT_D_PIN_0, PORT_PIN_IN, PORT_MODE_1, PULL_UP, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_1, PORT_PIN_IN, PORT_MODE_0, OFF, STD_HIGH, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_2, PORT_PIN_IN, PORT_MODE_1, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_3, PORT_PIN_IN, PORT_MODE_1, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_4, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_5, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_6, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_D, PORT_D_PIN_7, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    
    /* PORT E pins*/
    /* UART7 Pins */
    PORT_E, PORT_E_PIN_0, PORT_PIN_IN, PORT_MODE_1, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_E, PORT_E_PIN_1, PORT_PIN_IN, PORT_MODE_1, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,

    PORT_E, PORT_E_PIN_2, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_E, PORT_E_PIN_3, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_E, PORT_E_PIN_4, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_E, PORT_E_PIN_5, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,

    
    /* PORT F pins*/
    PORT_F, PORT_F_PIN_0, PORT_PIN_IN,  PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_F, PORT_F_PIN_1, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_F, PORT_F_PIN_2, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    PORT_F, PORT_F_PIN_3, PORT_PIN_IN, PORT_MODE_0, OFF, STD_LOW, changeable, changeable, OPEN_DRAIN_OFF,
    /* SPI SS Ouput Pin*/
    PORT_F, PORT_F_PIN_4, PORT_PIN_OUT,  PORT_MODE_0, OFF, STD_HIGH, changeable,  changeable ,OPEN_DRAIN_OFF,
};

