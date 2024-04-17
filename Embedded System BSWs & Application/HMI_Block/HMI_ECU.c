 /******************************************************************************
 *
 * Module: Main Source File for The HMI Block
 *
 * File Name: HMI_ECU.c
 *
 * Description: Source File for HMI ECU Block Functions
 *
 * Created on: Dec 9, 2021
 *
 * Authors: Mourad Eldin Nash'at , Abdelaziz Abu Zaid
 *
 *******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "HMI_ECU.h"

/*******************************************************************************
 *                     		      Main Function                                *
 *******************************************************************************/

int main(void)
{
    uint8 command;
    /* Initialize Drivers to be ready to use when it is needed */
    Drivers_Init();
    LCD_displayString("2looo");
    Delay_ms(1000);
    LCD_clearScreen();
    /* Super Loop */
    while (1) {
        command = Uart_ReceiveByte(CONTROL_BLOCK_UART);
        LCD_clearScreen();
        switch (command)
        {
        case FIRST_TIME_CMD:
            LCD_displayStringRowColumn(0, 2, "First Time Setup");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case SETUP_PASSWORD_CMD:
            LCD_displayString("1: Enter password");
            LCD_moveCursor(1,7);
            getPassword();
            LCD_clearScreen();
            LCD_displayString("2: Re-Enter password");
            LCD_moveCursor(1,7);
            getPassword();
            break;
        case PASSWORD_MISSMATCH_CMD:
            LCD_displayString("Passwords Missmatch!");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case GET_PASSWORD_CMD:
            LCD_displayString("Enter your password");
            LCD_moveCursor(1, 7);
            getPassword();
            break;
        case WRONG_PASSWORD_CMD:
            LCD_displayStringRowColumn(0, 2, "Wrong Password!");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case SETUP_RFID_CMD:
            LCD_displayString("Enter your 1st tag");
            getRfidTag();
            
            LCD_clearScreen();
            LCD_displayString("Enter your 2nd tag");
            getRfidTag();
            break;
        case GET_RFID_CMD:
            LCD_displayStringRowColumn(0, 3,"Scan your tag");
            getRfidTag();
            break;
        case TAG_FAILED_CMD:
            LCD_displayStringRowColumn(0, 4,"Tag Failed!");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case LOOK_AT_CAMERA_CMD:
            LCD_displayString("Smile to the camera!");
            break;
        /* FOR DEBUGGING PURPOSES */
        case FACE_SETUP_FAILED_CMD:
            LCD_displayString("Face ID Failed,Retry");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case SETUP_COMPLETE_CMD:
            LCD_displayString("Setup Complete! :)");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case DISPLAY_OPTIONS_CMD:
            /* Display Available Options on The Screen */
            LCD_displayString("1: Unlock The Engine");
            LCD_moveCursor(1, 0);
            LCD_displayString("2: Change Passcode");
            LCD_moveCursor(2, 0);
            LCD_displayString("3: Reset Credentials");
            LCD_moveCursor(3, 0);
            LCD_displayString("4: Fast RESET");
            getOption();
            break;
        case ACCESS_GRANTED_CMD:
            LCD_displayString("Access Granted!");
            Delay_ms(LCD_MESSAGE_DELAY);
            break;
        case LOCK_CMD:
            LCD_displayStringRowColumn(0, 3,"System Locked!");
            LCD_displayStringRowColumn(1,1,"Retry in 1 Minutes");
            break;
        case PASSWORD_CHANGED_CMD:
            LCD_displayString("Password Changed!");
            break;
        case SYSTEM_RESET_CREDENTIALS_CMD:
            LCD_displayString("Credential Reset!");
            break;
        case OTP_CMD:
            LCD_displayStringRowColumn(0, 5,"Enter OTP:");
            LCD_moveCursor(1, 6);
            getOTP();
            break;
        case WRONG_OTP_CMD:
            LCD_displayStringRowColumn(0, 5, "Wrong OTP!");
            LCD_displayStringRowColumn(1,3, "System Locked!");
            break;
        default:
            LCD_displayString("Undefined CMD!");
            break;
        }
    }
}

/*******************************************************************************************************
 * [Name]: Drivers_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Initializing of (MCAL) Drivers like UART and (HAL) Drivers
 * like LCD and Enabling Global Interrupt (I-Bit) in HMI Block.
 ********************************************************************************************************/
void Drivers_Init(void){
    Port_Init(&Port_Configuration);
    Dio_Init(&Dio_Configuration);
    Uart_Init(&Uart_Configuration);
    Spi_Init(&Spi_Configuration);
    RFID_Init();
    LCD_init();
}


void getPassword(void){
    /* Array to hold the passcode */
    uint8 passCode[PASSCODE_LENGTH] = { 0 };
    /* A counter to loop through the passcode array */
    uint8 passCodeCounter = 0;
    /* A variable to hold the pressed key */
    uint8 pressedKey = 0;
    /* A variable to read the continue command */
    uint8 continueCMD = 0;

    /* loop through the passcode array and save the input pressed key */
    for(passCodeCounter = 0; passCodeCounter < PASSCODE_LENGTH; passCodeCounter++){
        /* Get the pressed key from the keypad */
        pressedKey = KEYPAD_getPressedKey();
        passCode[passCodeCounter] = pressedKey;
        /* Make sure it's a number not a character */
        if((pressedKey >= 0) && (pressedKey <= 9)){
            LCD_moveCursor(1, 7 + passCodeCounter);
            LCD_displayCharacter('0' + pressedKey);
        } else {
            LCD_moveCursor(1, 7 + passCodeCounter);
            LCD_displayCharacter(pressedKey);
        }

        Delay_ms(250); /* Give time to read the pressed key */
        LCD_moveCursor(1, 7 + passCodeCounter);
        LCD_displayCharacter('*');

        /* A small delay to avoid button de-bouncing */
        Delay_ms(KEYPAD_DELAY);
    } /* end of for loop */

    /* Send the password to control block after reading it from the user */
    for(passCodeCounter = 0; passCodeCounter < PASSCODE_LENGTH; passCodeCounter++){
        Uart_SendByte(CONTROL_BLOCK_UART, passCode[passCodeCounter]);
        continueCMD = Uart_ReceiveByte(CONTROL_BLOCK_UART);
    } /* end of for loop */
} /* end of getPassword function */



void getOTP(void){
    /* Array to hold the passcode */
    uint8 otpCode[OTP_LENGTH] = { 0 };
    /* A counter to loop through the passcode array */
    uint8 otpCounter = 0;
    /* A variable to hold the pressed key */
    uint8 pressedKey = 0;
    /* A variable to read the continue command */
    uint8 continueCMD = 0;

    /* loop through the otp array and save the input pressed key */
    for(otpCounter = 0; otpCounter < OTP_LENGTH; otpCounter++){
        /* Get the pressed key from the keypad */
        pressedKey = KEYPAD_getPressedKey();
        otpCode[otpCounter] = pressedKey;
        /* Make sure it's a number not a character */
        if((pressedKey >= 0) && (pressedKey <= 9)){
            LCD_moveCursor(1, 7 + otpCounter);
            LCD_displayCharacter('0' + pressedKey);
        } else {
            LCD_moveCursor(1, 7 + otpCounter);
            LCD_displayCharacter(pressedKey);
        }

        Delay_ms(250); /* Give time to read the pressed key */
        LCD_moveCursor(1, 7 + otpCounter);
        LCD_displayCharacter('*');

        /* A small delay to avoid button de-bouncing */
        Delay_ms(KEYPAD_DELAY);
    } /* end of for loop */

    /* Send the otp code to control block after reading it from the user */
    for(otpCounter = 0; otpCounter < OTP_LENGTH; otpCounter++){
        Uart_SendByte(CONTROL_BLOCK_UART, otpCode[otpCounter]);
        continueCMD = Uart_ReceiveByte(CONTROL_BLOCK_UART);
    } /* end of for loop */
} /* end of getOTP function */


void getRfidTag(void){
    /* Array to hold the value of the unique id of the rfid tag */
    uint8 rfidTag[RFID_UNIQUE_ID_LENGTH];
    /* A counter to loop through the array of the uid */
    uint8 uidCounter = 0;
    /* A variable to read the continue command */
    uint8 continueCMD = 0;

    /* Read the rfid tag */
    rfidReadTag(rfidTag);

    /* Send the rfid tag to the control block after scanning it */
    for(uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++){
        Uart_SendByte(CONTROL_BLOCK_UART, rfidTag[uidCounter]);
        continueCMD = Uart_ReceiveByte(CONTROL_BLOCK_UART);
    } /* end of for loop */
} /* end of getRfidTag function */

void rfidReadTag(uint8 * a_rfid_tag){
    uint8 byte;

    byte = RFID_Read(ComIEnReg);
    RFID_Write(ComIEnReg, byte | 0x20);
    byte = RFID_Read(DivIEnReg);
    RFID_Write(DivIEnReg, byte | 0x80);

    while (1) {
        byte = RFID_Request(PICC_REQALL, a_rfid_tag);
        if (byte == CARD_FOUND)
        {
            byte = RFID_getCardSerial(a_rfid_tag);
            /* Str has the UID of the rfid tag */

                 /* Delete me later */
            if (byte == CARD_FOUND)
            {
                LCD_clearScreen();
                for (byte = 0;byte < 8;byte++) {
                    LCD_displayHex(a_rfid_tag[byte]);
                }
                Delay_ms(2500);
                return;
            }
        }
        Delay_ms(1000);
    }
}

void getOption(void){
    /* A variable to hold the chosen option */
    uint8 option = 0;

    /* Loop until the user chooses a valid option */
    do {
        option = KEYPAD_getPressedKey();
        Delay_ms(KEYPAD_DELAY);
    } while (option != 1 && option != 2 && option != 3 && option != 4);

    /* Send the option back to the control block */
    Uart_SendByte(CONTROL_BLOCK_UART, option);
} /* end of getOption function */

