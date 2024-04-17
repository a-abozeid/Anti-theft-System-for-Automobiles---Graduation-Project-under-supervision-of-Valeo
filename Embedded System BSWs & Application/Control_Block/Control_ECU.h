 /******************************************************************************
 *
 * Module: Main Source File for The Control Block
 *
 * File Name: Control_ECU.h
 *
 * Description: Header File for Control ECU Block Functions
 *
 * Created on: Dec 9, 2021
 *
 * Authors: Mourad Eldin Nash'at , Abdelaziz Abu Zaid
 *
 *******************************************************************************/


#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "Std_Types.h"
#include "Dio.h"
#include "Port.h"
#include "Control_ECU.h"
#include "Uart.h"
#include "I2c.h"
#include "external_eeprom.h"
#include "Sw_Delay.h"
#include "gsm.h"
#include "gps.h"
#include "GPT.h"

/*******************************************************************************
 *                                Definitions                                 *
 *******************************************************************************/

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

#define LOCK_TIME 30000
#define INCORRECT 0
#define CORRECT 1
#define LOCK 2

#define RFID_UNIQUE_ID_LENGTH (8u)

/* EEPROM Addresses */
#define FIRST_TIME_ADDRESS 0x000
#define PASSWORD_ADDRESS 0x020
#define RFID_ADDRESS 0x040
#define WRONG_ATTEMPTS_ADDRESS 0x060
#define NO_AUTH_USED_ADDRESS 0x080

#define PASSWORD_LENGTH 5
#define MAX_NUMBER_OF_FAILED_ATTEMPTS 3
#define MAX_NUMBER_OF_LOCKS 3
#define numOfAvAuthMethods 3

#define OTP_LENGTH 8

/* New Day, New Beggining */
/* HMI Commands */
#define FIRST_TIME_CMD (1u)
#define PASSWORD_MISSMATCH_CMD (2u)
#define WRONG_PASSWORD_CMD (3u)
#define TAG_FAILED_CMD (4u)
#define LOOK_AT_CAMERA_CMD (5u)
#define ACCESS_GRANTED_CMD (6u)
#define LOCK_CMD (7u)
#define SETUP_COMPLETE_CMD (8u)
#define FACE_SETUP_FAILED_CMD (9u)

#define SETUP_PASSWORD_CMD  (10u)
#define SETUP_RFID_CMD (11u)
#define GET_PASSWORD_CMD (12u)
#define GET_RFID_CMD (13u)
#define DISPLAY_OPTIONS_CMD (14u)
#define GET_CHOSEN_OPTION_CMD (15u)
#define PASSWORD_CHANGED_CMD (16u)
#define SYSTEM_RESET_CREDENTIALS_CMD (17u)
#define OTP_CMD (18u)
#define WRONG_OTP_CMD (19u)


/* Raspberry Pi Commands */
#define RASP_FIRST_TIME_CMD 'y'
#define RASP_AUTH_CMD 'n'
#define RASP_AUTH_FAILURE_CMD 'f'
#define RASP_AUTH_SUCCESS_REPORT 't'
#define RASP_SETUP_FAILED_ERROR 'R'
#define RASP_SETUP_SUCCEEDED_REPORT 'W'
#define CONTINUE_CMD 'C'
/*******************************************************************************
 *                         		Types Declaration                              *
 *******************************************************************************/

/* Typedef Enumeration to make Sytsem_State Date Type with values BLOCKED and FREE */
typedef enum
{
	BLOCKED , FREE

}System_State;



/*******************************************************************************
 *                     		  Functions Prototypes                             *
 *******************************************************************************/

/*******************************************************************************************************
 * [Name]: Drivers_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Initializing of (MCAL) Drivers like UART & I2C and (HAL)
 * Drivers like GPS/GSM Modules and Enabling Global Interrupt (I-Bit) in Control Block.
 ********************************************************************************************************/
void Drivers_Init(void);

void systemSetup(void);

void passwordSetup(void);

void rfidSetup(void);

void faceSetup(void);

uint8 faceAuth(void);
uint8 rfidAuth(void);
uint8 passwordAuth(void);
boolean systemAuth(void);
void resetCredentials(void);
void generateOTP(uint8* numbers, uint8 length);
#endif /* CONTROL_ECU_H_ */

