 /******************************************************************************
 *
 * Module: Main Source File for The HMI Block
 *
 * File Name: HMI_ECU.h
 *
 * Description: Header File for HMI ECU Block Functions
 *
 * Created on: Dec 9, 2021
 *
 * Authors: Mourad Eldin Nash'at , Abdelaziz Abu Zaid
 *
 *******************************************************************************/


#ifndef HMI_ECU_H_
#define HMI_ECU_H_


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
/* MCAL Drivers */
#include "Port.h"
#include "Dio.h"
#include "Uart.h"
#include "Spi.h"

/* HAL Drivers */
#include "lcd.h"
#include "keypad.h"
#include "RFID.h"

/* Utility Functions */
#include "Sw_Delay.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define KEYPAD_DELAY 250
#define LCD_MESSAGE_DELAY 2000

#define numOfAvAuthMethods 3
#define PASSCODE_LENGTH 5
#define OTP_LENGTH 8
#define INCORRECT 0
#define CORRECT 1
#define PASSWORD_OR_LOCK 3
#define LOCK 2
#define FREE_SYSTEM 5
#define LOCK_TIME 60000


/* New Day, New Beggining */
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

uint8 isFirstTime();

/*******************************************************************************************************
 * [Name]: Drivers_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Initializing of (MCAL) Drivers like UART and (HAL) Drivers
 * like LCD and Enabling Global Interrupt (I-Bit) in HMI Block.
 ********************************************************************************************************/
void Drivers_Init(void);


/*******************************************************************************************************
 * [Name]: Receive_First_Time_Check
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Receiving a certain Byte ('Y' or 'N') from The Control Block
 * to to check whether its the first time use of the system or not.
 ********************************************************************************************************/
void Receive_First_Time_Check(void);


/*******************************************************************************************************
 * [Name]: Setup_New_Passcode
 * [Parameters]: uint8 *pass1 , uint8 *pass2
 * [Return]: void (none)
 * [Description]: The Function responsible for Creating a new Passcode for The System for the first time
 * use or when changing The Passcode and check it's correctness.
 ********************************************************************************************************/
void Setup_New_Passcode(uint8 *pass1 , uint8 *pass2);


/*******************************************************************************************************
 * [Name]: Passcode_Check_Condition
 * [Parameters]: uint8 *pass1 , uint8 *pass2
 * [Return]: Boolean Value (0 or 1)
 * [Description]: The Function responsible for The Condition to check the two Entered Passcodes at
 * The Setup or Change Processes.
 ********************************************************************************************************/
boolean Passcode_Check_Condition(uint8 *pass1 , uint8 *pass2);


/*******************************************************************************************************
 * [Name]: Enter_Passcode
 * [Parameters]: uint8 *pass
 * [Return]: void (none)
 * [Description]: The Function responsible for Entering a Passcode of certain number of Numeric
 * Characters using The Keypad.
 ********************************************************************************************************/
void Enter_Passcode(uint8 *pass);


/*******************************************************************************************************
 * [Name]: Options_Menu
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Displaying Options Menu on The LCD to decide what action
 * to do and display it's result.
 ********************************************************************************************************/
void Options_Menu(void);


/*******************************************************************************************************
 * [Name]: Block_System
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Blocking The System at a certain Point
 ********************************************************************************************************/
void Block_System(void);


/*******************************************************************************************************
 * [Name]: Free_System
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for getting The System back from Blocked state to Free State.
 ********************************************************************************************************/
void Free_System(void);

void passwordSetup(void);

uint8 passwordAuth(void);

void rfidSetup(void);

uint8 rfidAuth(void);

void faceSetup(void);

uint8 faceAuth(void);

void systemAuth(void);


void getRfidTag(void);
void rfidReadTag(uint8 * a_rfid_tag);

void getPassword(void);

void getOTP(void);
void getOption(void);

#endif /* HMI_ECU_H_ */


