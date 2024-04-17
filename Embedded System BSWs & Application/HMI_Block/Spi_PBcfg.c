 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: Spi_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - SPI Driver
 *
 * Author: Mourad Eldin Nash'at
 ******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "Spi.h"



/*******************************************************************************
*                           Configurations Structure                           *
*******************************************************************************/ 

/* PB structure used with SPI_Init API */
const Spi_ConfigType Spi_Configuration = 
{
    /* SSI0 Settings */
    SSI_OFF, MASTER_MODE , SYTSTEM_CLOCK , FREESCALE_SPI_FRAME_FORMAT , FIRST_EDGE_TRANSITION , STEADY_STATE_LOW , EIGHT_BIT_DATA,0,0,

    /* SSI1 Settings */
    SSI_OFF, MASTER_MODE , SYTSTEM_CLOCK , FREESCALE_SPI_FRAME_FORMAT , FIRST_EDGE_TRANSITION , STEADY_STATE_LOW , EIGHT_BIT_DATA,0,0,
    
    /* SSI2 Settings */
    SSI_OFF, MASTER_MODE , SYTSTEM_CLOCK , FREESCALE_SPI_FRAME_FORMAT , FIRST_EDGE_TRANSITION , STEADY_STATE_LOW , EIGHT_BIT_DATA,0,0,
    
    /* SSI3 Settings */
    SSI_ON, MASTER_MODE , SYTSTEM_CLOCK , FREESCALE_SPI_FRAME_FORMAT , FIRST_EDGE_TRANSITION , STEADY_STATE_LOW , EIGHT_BIT_DATA,4,0,
};