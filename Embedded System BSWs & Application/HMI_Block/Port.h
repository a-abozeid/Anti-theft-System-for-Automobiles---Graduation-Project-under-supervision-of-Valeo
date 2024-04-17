 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT init */
#define PORT_INIT_SID                                  ((uint8)0x00)

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Service ID for PORT set pin direction */
#define PORT_SET_PIN_DIRECTION_SID                     ((uint8)0x01)
#endif

/* Service ID for PORT refresh port direction */
#define PORT_REFRESH_PORT_DIRECTION_SID                ((uint8)0x02)

#if (PORT_VERSION_INFO_API == STD_ON)
/* Service ID for PORT get version info */
#define PORT_GET_VERSION_INFO_SID                      ((uint8)0x03)
#endif

/* Service ID for PORT set pin mode */
#define PORT_SET_PIN_MODE_SID                          ((uint8)0x04)


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID */
#define PORT_E_PARAM_PIN                          ((uint8)0x0A)

/* DET code to report Port Pin is not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE             ((uint8)0x0B)

/* Port_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG                       ((uint8)0x0C)

/* DET code to report Invalid Port Pin Mode */
#define PORT_E_PARAM_INVALID_MODE                 ((uint8)0x0D)

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                  ((uint8)0x0E)

/* API service called without module initialization */
#define PORT_E_UNINIT                             ((uint8)0x0F)

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                      ((uint8)0x10)
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Data type for the symbolic name of a port pin. */
typedef uint8 Port_PinType;

/* Data type for the symbolic name of a port */
typedef uint8 Port_PortType;

/* Different port pin modes. */
typedef uint8 Port_PinModeType;

/* Number of total GPIO pins */
#define PORT_PINS_NUM 43 

/* largest port mode number */
#define PORT_MODE_MAXIMUM_NUMBER        (uint8)15

/* Different values for Port_PinModeType */
#define PORT_MODE_0                     (uint8)0 /*GPIO mode*/
#define PORT_MODE_1                     (uint8)1
#define PORT_MODE_2                     (uint8)2
#define PORT_MODE_3                     (uint8)3
#define PORT_MODE_4                     (uint8)4
#define PORT_MODE_5                     (uint8)5
#define PORT_MODE_6                     (uint8)6
#define PORT_MODE_7                     (uint8)7
#define PORT_MODE_8                     (uint8)8
#define PORT_MODE_9                     (uint8)9
#define PORT_MODE_10                    (uint8)10
#define PORT_MODE_11                    (uint8)11
#define PORT_MODE_12                    (uint8)12
#define PORT_MODE_13                    (uint8)13
#define PORT_MODE_14                    (uint8)14
#define PORT_MODE_15                    (uint8)15

#define PORT_MODE_ADC                   PORT_MODE_15



/* Possible directions of a port pin. */
typedef enum {
    PORT_PIN_IN, PORT_PIN_OUT
} Port_PinDirectionType;

/* Possible modes of a port internal resistor */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Possible modes for direction/mode changeability for a pin */
typedef enum 
{
    unchangeable, changeable
}Port_Changeability;

/* Possible modes for open-drain */
typedef enum{
    OPEN_DRAIN_OFF, OPEN_DRAIN_ON
} Port_OpenDrainMode;


/* Description: Structure to configure each individual PIN:
 *	1. port_num: the number of port which the pin belongs to.
 *	2. pin_num: the number of the pin in the port.
 *  3. pin_direction: the direction of pin --> INPUT or OUTPUT
 *  4. pin_mode: to select the mode that the pin operates on.
 *  5. InternalResistor: the internal resistor --> Disable, Pull up or Pull down
 *  6. initial_value: initial value of the pin.
 *  7. pin_direction_changeability: changeable if pin direction is changeable during runtime
 *                                unchangeable if pin direction isn't changable during runtime
 *  8. pin_mode_changeability: changeable  -> if pin mode is changeable during runtime
 *                            unchangeable -> if pin mode isn't changable during runtime
 */
typedef struct{
    Port_PortType port_num;
    Port_PinType pin_num;
    Port_PinDirectionType pin_direction;
    Port_PinModeType pin_mode;
    Port_InternalResistor pin_internal_resistor;
    uint8 pin_initial_value;
    Port_Changeability pin_direction_changeability; 
    Port_Changeability pin_mode_changeability;
    Port_OpenDrainMode open_drain_mode;
} Port_ConfigPin;

typedef struct{
    Port_ConfigPin Pins[PORT_PINS_NUM];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function prototype for PORT init API */
void Port_Init(const Port_ConfigType* ConfigPtr); 

#if  (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function prototype for PORT set pin direction API */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function prototype for PORT refresh port direction API */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/* Function prototype for PORT get version info API */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Function prototype for PORT set pin mode API */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */

