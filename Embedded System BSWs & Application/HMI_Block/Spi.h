 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: SPI.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - SPI Driver
 *
 * Author: Mourad Eldin Nash'at
 ******************************************************************************/


#ifndef SPI_H
#define SPI_H

/* Id for the company in the AUTOSAR */
#define SPI_VENDOR_ID    (1000U)

/* SPI Module Id */
#define SPI_MODULE_ID    (132U)

/* SPI Instance Id */
#define SPI_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define SPI_SW_MAJOR_VERSION           (1U)
#define SPI_SW_MINOR_VERSION           (0U)
#define SPI_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define SPI_AR_RELEASE_MAJOR_VERSION   (4U)
#define SPI_AR_RELEASE_MINOR_VERSION   (0U)
#define SPI_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for SPI Status
 */
#define SPI_INITIALIZED                (1U)
#define SPI_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and SPI Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* SPI Pre-Compile Configuration Header file */
#include "Spi_Cfg.h"

/* AUTOSAR Version checking between Spi_Cfg.h and Spi.h files */
#if ((SPI_CFG_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)\
 ||  (SPI_CFG_AR_RELEASE_MINOR_VERSION != SPI_AR_RELEASE_MINOR_VERSION)\
 ||  (SPI_CFG_AR_RELEASE_PATCH_VERSION != SPI_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Spi_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Spi_Cfg.h and Spi.h files */
#if ((SPI_CFG_SW_MAJOR_VERSION != SPI_SW_MAJOR_VERSION)\
 ||  (SPI_CFG_SW_MINOR_VERSION != SPI_SW_MINOR_VERSION)\
 ||  (SPI_CFG_SW_PATCH_VERSION != SPI_SW_PATCH_VERSION))
  #error "The SW version of Spi_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                          API Service Id Macros                             *
 ******************************************************************************/



/*******************************************************************************
 *                              DET Error Codes                                *
 *******************************************************************************/

/* API service called with wrong parameter */
#define SPI_E_PARAM_CHANNEL             ((uint8)0x0A)
#define SPI_E_PARAM_JOB                 ((uint8)0x0B)
#define SPI_E_PARAM_SEQ                 ((uint8)0x0C)
#define SPI_E_PARAM_LENGTH              ((uint8)0x0D)
#define SPI_E_PARAM_UNIT                ((uint8)0x0E)

/* APIs called with a Null Pointer */   
#define SPI_E_PARAM_POINTER             ((uint8)0x10)

/* API service used without module initialization */
#define SPI_E_UNINIT                    ((uint8)0x1A)

/*API SPI_Init service called while the SPI driver has already been initialized */
#define SPI_E_ALREADY_INITIALIZED       ((uint8)0x4A)



/*******************************************************************************
 *                            Runtime Error Codes                              *
 *******************************************************************************/

/* Services called in a wrong sequence */
#define SPI_E_SEQ_PENDING               ((uint8)0x2A)

/* Synchronous transmission service called at wrong time */
#define SPI_E_SEQ_IN_PROCESS            ((uint8)0x3A)



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

#define SSI_MODULE_NUMBERS               (4u)

#define SSI_SSE_BIT                      (1u)

#define SSI_TNF_MASK                     (2u)

#define SSI_BSY_MASK                     (0x10)
/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define SPI_DEFAULT_DATA_VALUE 0xFF


typedef enum 
{
    SSI0_MODULE_NUMBER,
    SSI1_MODULE_NUMBER,
    SSI2_MODULE_NUMBER,
    SSI3_MODULE_NUMBER,

} SSI_ModuleNumber;

typedef enum{
    SSI_OFF,
    SSI_ON
} SSI_StatusMode;

typedef enum
{
    MASTER_MODE,
    SLAVE_MODE_OUTPUT_ENABLED,
    SLAVE_MODE_OUTPUT_DISABLED,

}SSI_MasterSlave_Mode;


typedef enum
{
    SYTSTEM_CLOCK,
    PIOSC,

}SSI_ClockConfiguration;


typedef enum
{
    FREESCALE_SPI_FRAME_FORMAT,
    TI_SS_FRAME_FORMAT,
    MICROWIRE_FRAME_FORAMT,

}SSI_FrameFormatSelect;


typedef enum
{
    FIRST_EDGE_TRANSITION,
    SECOND_EDGE_TRANSITION,

}SSI_SerialClockPhase;


typedef enum
{
    STEADY_STATE_LOW,
    STEADY_STATE_HIGH,

}SSI_SerialClockPolarity;

typedef enum
{
    FOUR_BIT_DATA,
    FIVE_BIT_DATA,
    SIX_BIT_DATA,
    SEVEN_BIT_DATA,
    EIGHT_BIT_DATA,
    NINE_BIT_DATA,
    TEN_BIT_DATA,
    ELEVEN_BIT_DATA,
    TWELVE_BIT_DATA,
    THIRTEEN_BIT_DATA,
    FOURTEEN_BIT_DATA,
    FIFTEEN_BIT_DATA,
    SIXTEEN_BIT_DATA,

}SSI_DateSizeSelect;



typedef struct 
{   
    SSI_StatusMode statusMode;
    SSI_MasterSlave_Mode masterSlaveMode;
    SSI_ClockConfiguration clockConfiguration;
    SSI_FrameFormatSelect frameFormatSelect;
    SSI_SerialClockPhase clockPhase;
    SSI_SerialClockPolarity clockPolarity;
    SSI_DateSizeSelect dataSize;
    /* Prescaller Registers */
    uint8 CPSDVSRRegValue; 
    uint8 SCRRegValue;

} Spi_ConfigModule;

typedef struct 
{
    Spi_ConfigModule SSI_Modules[SSI_MODULE_NUMBERS];
} Spi_ConfigType;



/*******************************************************************************
 *                     		  Functions Prototypes                             *
 *******************************************************************************/

/************************************************************************************
* Service Name: Spi_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service for SPI initialization.
************************************************************************************/
void Spi_Init(const Spi_ConfigType * ConfigPtr); 


/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_SendReceiveByte(SSI_ModuleNumber moduleNumber,uint8 data);


/*******************************************************************************
 *                         External Global Variables                           *
 *******************************************************************************/

extern const Spi_ConfigType Spi_Configuration;



#endif /* SPI_H */