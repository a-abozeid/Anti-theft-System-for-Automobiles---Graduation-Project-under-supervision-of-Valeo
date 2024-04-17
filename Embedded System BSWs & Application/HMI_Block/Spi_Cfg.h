 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: Spi_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - SPI Driver
 *
 * Author: Mourad Eldin Nash'at
 ******************************************************************************/

#ifndef SPI_CFG_H
#define SPI_CFG_H

/*
 * Module Version 1.0.0
 */
#define SPI_CFG_SW_MAJOR_VERSION              (1U)
#define SPI_CFG_SW_MINOR_VERSION              (0U)
#define SPI_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define SPI_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define SPI_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define SPI_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/* Pre-compile option for Development Error Detection */
#define SPI_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Get Version Info API */
#define SPI_VERSION_INFO_API                (STD_ON)


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define RFID_SPI SSI3_MODULE_NUMBER



#endif /* SPI_CFG_H */