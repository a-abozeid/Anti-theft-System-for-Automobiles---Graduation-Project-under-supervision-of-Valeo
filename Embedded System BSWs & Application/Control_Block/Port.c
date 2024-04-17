 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigPin * Port_PinsPtr = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr)
{
    /* A counter that will be used to loop through the array of structures of the PORT configuration structure */
    Port_PinType pinsCounter = 0; 

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR; 

    /* A variable that will be used to buy some time for the clock to be initalized for the registers */
    volatile uint32 delay = 0;

    /* Make the global Port_PinsPtr point to the PB array of ConfigPin structures */
    /* This global pointer is global to be used by other functions to read the PB configuration structures */
    Port_PinsPtr = (ConfigPtr->Pins);

    /* Development Error Checking */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
        /* loop through the array of ConfigPin structures */
        for (pinsCounter = 0; pinsCounter < PORT_PINS_NUM; pinsCounter++)
        {
            switch (Port_PinsPtr[pinsCounter].port_num)
            {
            case GPIO_PORTA_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case GPIO_PORTB_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case GPIO_PORTC_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case GPIO_PORTD_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case GPIO_PORTE_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case GPIO_PORTF_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            }

            /* Enable clock for PORT and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= (1<<(Port_PinsPtr[pinsCounter].port_num));
            delay = SYSCTL_REGCGC2_REG;

            /* Special Pins */
            /*  Pins that need to use lock and commit registers before accessing the rest of their registers like PD7 and PF0 and other 
                special pins like the JTAG pins PC0 to PC3 which should be ignored */
            if (((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTD_ID) && (Port_PinsPtr[pinsCounter].pin_num == GPIO_PD7)) || ((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTF_ID) && (Port_PinsPtr[pinsCounter].pin_num == GPIO_PF0))) /* PD7 or PF0 */
            {
                /* Unlock the GPIOCR register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;  

                /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
            }
            else if ((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTC_ID) && (Port_PinsPtr[pinsCounter].pin_num <= GPIO_PC3)) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is one of the JTAG pins */
                continue;
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

        
            if(Port_PinsPtr[pinsCounter].pin_mode != PORT_MODE_ADC){
                if(Port_PinsPtr[pinsCounter].pin_mode == PORT_MODE_0){
                    /* GPIO mode*/
                    /* Disable alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
                } else {
                    /* Non - GPIO mode*/
                    /* Enable alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
                }

                /* Disable the analog function for this pin by clearing the corresponding bit in GPOIAMSEL register*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);

                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);

                /* setting GPIOPCTL is made in two steps*/
                /* FIRST: Clear the bits corresponding to the pin in GPIOPCTL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_PinsPtr[pinsCounter].pin_num) * 4)); 
                
                /* SECOND: Change the bits corresponding to the pin in GPIOPCTL register with the right mode*/
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (((uint32)(Port_PinsPtr[pinsCounter].pin_mode)) << (Port_PinsPtr[pinsCounter].pin_num * 4));
            
            } else {
                /* ADC mode*/
                /* SET Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);

                /* Enable the analog function for this pin by clearing the corresponding bit in GPOIAMSEL register*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);

                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
            }

              
            /* Check the direction of the pin */
            if (Port_PinsPtr[pinsCounter].pin_direction == PORT_PIN_OUT)
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 

                if (Port_PinsPtr[pinsCounter].pin_initial_value == STD_HIGH)
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
                }
                else
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
                }
            }
            else if (Port_PinsPtr[pinsCounter].pin_direction == PORT_PIN_IN)
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 

                if (Port_PinsPtr[pinsCounter].pin_internal_resistor == PULL_UP)
                {
                    /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
                }
                else if (Port_PinsPtr[pinsCounter].pin_internal_resistor == PULL_DOWN)
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
                }
                else
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 

                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); 
                }
            }
            else
            {
                /* Do Nothing */
            }

            /* Open-Drain Setting */
            if (Port_PinsPtr[pinsCounter].open_drain_mode == OPEN_DRAIN_ON) {
                /* Set the corresponding bit in the open-drain register to enable open drain functionality of the pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_OPEN_DRAIN_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
            }
            else if (Port_PinsPtr[pinsCounter].open_drain_mode == OPEN_DRAIN_OFF) {
                /* Clear the corresponding bit in the open-drain register to disable open drain functionality of the pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_OPEN_DRAIN_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
            }
            else {
                /* Do Nothing */
            }
        }
        Port_Status = PORT_INITIALIZED;
    }
}


#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Pin ID number.
*                  Direction - Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR; 

    /* A variable that will be used to buy some time for the clock to be initalized for the registers */
    volatile uint32 delay = 0;

    /* Will be used to check if the driver passed the DET error checking or not */
    boolean error = FALSE;
     
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/* Check if the pin is within the valid range */
	if (PORT_PINS_NUM <= Pin)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

    /* Check if the pin direction is unchangable */
    if(unchangeable == Port_PinsPtr[Pin].pin_direction_changeability){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
    }
    else 
    {
        /* No Action Required */
    }

#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
        switch (Port_PinsPtr[Pin].port_num)
        {
        case GPIO_PORTA_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case GPIO_PORTB_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case GPIO_PORTC_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case GPIO_PORTD_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case GPIO_PORTE_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case GPIO_PORTF_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        /* Enable clock for PORT and allow time for clock to start*/
        SYSCTL_REGCGC2_REG |= (1 << (Port_PinsPtr[Pin].port_num));
        delay = SYSCTL_REGCGC2_REG;

        /* Special Pins */
        /*  Pins that need to use lock and commit registers before accessing the rest of their registers like PD7 and PF0 and other 
            special pins like the JTAG pins PC0 to PC3 which should be ignored */
        if (((Port_PinsPtr[Pin].port_num == GPIO_PORTD_ID) && (Port_PinsPtr[Pin].pin_num == GPIO_PD7)) || ((Port_PinsPtr[Pin].port_num == GPIO_PORTF_ID) && (Port_PinsPtr[Pin].pin_num == GPIO_PF0))) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_PinsPtr[Pin].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if ((Port_PinsPtr[Pin].port_num == GPIO_PORTC_ID) && (Port_PinsPtr[Pin].pin_num <= GPIO_PC3)) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is one of the JTAG pins */
            return;
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        /* Check the new direction of the pin */
        if (PORT_PIN_OUT == Direction)
        {
            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[Pin].pin_num);
        }
        else if (PORT_PIN_IN == Direction)
        {
            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[Pin].pin_num);
        }
        else
        {
            /* Do Nothing */
        }
    }
	else
	{
		/* No Action Required */
	}
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    /* A counter that will be used to loop through the array of structures of the PORT configuration structure */
    Port_PinType pinsCounter = 0; 

    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR; 

    /* A variable that will be used to buy some time for the clock to be initalized for the registers */
    volatile uint32 delay = 0;

    /* Will be used to check if the driver passed the DET error checking or not */
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
        for(pinsCounter = 0; pinsCounter < PORT_PINS_NUM; pinsCounter++){
            /* To refresh the pin, its direction changeability must be sit to unchangale during run time */
            if(Port_PinsPtr[pinsCounter].pin_direction_changeability == changeable){
                continue; /* Skip this pin */
            }
            else 
            {
                switch (Port_PinsPtr[pinsCounter].port_num)
                {
                case GPIO_PORTA_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                    break;
                case GPIO_PORTB_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                    break;
                case GPIO_PORTC_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                    break;
                case GPIO_PORTD_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                    break;
                case GPIO_PORTE_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                    break;
                case GPIO_PORTF_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                    break;
                }

                /* Enable clock for PORT and allow time for clock to start*/
                SYSCTL_REGCGC2_REG |= (1 << (Port_PinsPtr[pinsCounter].port_num));
                delay = SYSCTL_REGCGC2_REG;

                /* Special Pins */
                /*  Pins that need to use lock and commit registers before accessing the rest of their registers like PD7 and PF0 and other 
                    special pins like the JTAG pins PC0 to PC3 which should be ignored */
                if (((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTD_ID) && (Port_PinsPtr[pinsCounter].pin_num == GPIO_PD7)) || ((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTF_ID) && (Port_PinsPtr[pinsCounter].pin_num == GPIO_PF0))) /* PD7 or PF0 */
                {
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                          /* Unlock the GPIOCR register */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                }
                else if ((Port_PinsPtr[pinsCounter].port_num == GPIO_PORTC_ID) && (Port_PinsPtr[pinsCounter].pin_num <= GPIO_PC3)) /* PC0 to PC3 */
                {
                    /* Do Nothing ...  this is one of the JTAG pins */
                    continue;
                }
                else
                {
                    /* Do Nothing ... No need to unlock the commit register for this pin */
                }

                /* Check the direction of the pin in PB configuration and refresh it */
                if (PORT_PIN_OUT == Port_PinsPtr[pinsCounter].pin_direction)
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
                }
                else if (PORT_PIN_IN == Port_PinsPtr[pinsCounter].pin_direction)
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_PinsPtr[pinsCounter].pin_num);
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
    }	
}

#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif

#if(PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number.
                   Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /* point to the required Port Registers base address */
    volatile uint32 * PortGpio_Ptr = NULL_PTR; 

    /* A variable that will be used to buy some time for the clock to be initalized for the registers */
    volatile uint32 delay = 0;

    /* Will be used to check if the driver passed the DET error checking or not */
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/* Check if the pin is within the valid range */
	if (PORT_PINS_NUM <= Pin)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

    /* Check if the pin mode is within the valid range */
    if(PORT_MODE_MAXIMUM_NUMBER < Mode){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
    }
    else 
    {
        /* No Action Required */
    }
    
    /* Check if the pin mode is unchangable */
    if(unchangeable == Port_PinsPtr[Pin].pin_mode_changeability){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
    }
    else 
    {
        /* No Action Required */
    }
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
        switch (Port_PinsPtr[Pin].port_num)
        {
        case GPIO_PORTA_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case GPIO_PORTB_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case GPIO_PORTC_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case GPIO_PORTD_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case GPIO_PORTE_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case GPIO_PORTF_ID:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        /* Enable clock for PORT and allow time for clock to start*/
        SYSCTL_REGCGC2_REG |= (1 << (Port_PinsPtr[Pin].port_num));
        delay = SYSCTL_REGCGC2_REG;


        /* Special Pins */
        /*  Pins that need to use lock and commit registers before accessing the rest of their registers like PD7 and PF0 and other 
            special pins like the JTAG pins PC0 to PC3 which should be ignored */
        if (((Port_PinsPtr[Pin].port_num == GPIO_PORTD_ID) && (Port_PinsPtr[Pin].pin_num == GPIO_PD7)) || ((Port_PinsPtr[Pin].port_num == GPIO_PORTF_ID) && (Port_PinsPtr[Pin].pin_num == GPIO_PF0))) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                          /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_PinsPtr[Pin].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if ((Port_PinsPtr[Pin].port_num == GPIO_PORTC_ID) && (Port_PinsPtr[Pin].pin_num <= GPIO_PC3)) /* PC0 to PC3 */
        {
            /* Do Nothing ...  this is one of the JTAG pins */
            return;
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if (Mode != PORT_MODE_ADC)
        {
            if (Mode == PORT_MODE_0)
            {
                /* GPIO mode*/
                /* Disable alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[Pin].pin_num);
            }
            else
            {
                /* Non - GPIO mode*/
                /* Enable alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[Pin].pin_num);
            }

            /* Disable the analog function for this pin by clearing the corresponding bit in GPOIAMSEL register*/
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinsPtr[Pin].pin_num);

            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PinsPtr[Pin].pin_num);

            /* setting GPIOPCTL is made in two steps*/
            /* FIRST: Clear the bits corresponding to the pin in GPIOPCTL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_PinsPtr[Pin].pin_num) * 4));

            /* SECOND: Change the bits corresponding to the pin in GPIOPCTL register with the right mode*/
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (((uint32)(Port_PinsPtr[Pin].pin_mode)) << (Port_PinsPtr[Pin].pin_num * 4));
        }
        else
        {
            /* ADC mode*/
            /* SET Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_PinsPtr[Pin].pin_num);

            /* Enable the analog function for this pin by clearing the corresponding bit in GPOIAMSEL register*/
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_PinsPtr[Pin].pin_num);

            /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_PinsPtr[Pin].pin_num);
        }
    }
}
#endif