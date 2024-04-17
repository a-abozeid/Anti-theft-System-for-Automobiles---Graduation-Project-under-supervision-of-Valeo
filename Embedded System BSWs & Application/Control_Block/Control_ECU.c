 /******************************************************************************
 *
 * Module: Main Source File for The Control Block
 *
 * File Name: Control_ECU.c
 *
 * Description: Source File for Control ECU Block Functions
 *
 * Created on: Dec 9, 2021
 *
 * Authors: Mourad Eldin Nash'at , Abdelaziz Abu Zaid
 *
 *******************************************************************************/

/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "Control_ECU.h"
#include "stdlib.h"
/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* ZBAAAALA */
/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")
/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")

#define NVIC_EN0_REG              (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1_REG              (*((volatile unsigned long *)0xE000E104))
#define NVIC_PRI7_REG             (*((volatile unsigned long *)0xE000E41C))
#define NVIC_PRI14_REG            (*((volatile unsigned long *)0xE000E438))
#define NVIC_PRI5_REG             (*((volatile unsigned long *)0xE000E414))
#define NVIC_PRI4_REG             (*((volatile unsigned long *)0xE000E410))

#define UART3_PRIORITY_MASK 0x1FFFFFFF
#define UART3_PRIORITY_LEVEL 2
#define UART3_PRIORITY_BITS_POS 29

#define GPIO_PORTF_PRIORITY_MASK      0xFF1FFFFF
#define GPIO_PORTF_PRIORITY_BITS_POS  21
#define GPIO_PORTF_INTERRUPT_PRIORITY 2

#define TIMER1A_PRIORITY_MASK 0xFFFF1FFF
#define TIMER1A_PRIORITY_LEVEL 3
#define TIMER1A_PRIORITY_BITS_POS 13

#define TIMER0A_PRIORITY_MASK 0x1FFFFFFF
#define TIMER0A_PRIORITY_LEVEL 4
#define TIMER0A_PRIORITY_BITS_POS 29


/* PORTF External Interrupts Registers */
#define GPIO_PORTF_IS_REG         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_REG        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_REG        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_REG         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS_REG        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_ICR_REG        (*((volatile unsigned long *)0x4002541C))


/* Global Variable of type System_State used to block The System at a certain point for an amount of time */
System_State state = BLOCKED;

/* Global Variable that holds The Value of Times The Passcode is entered in case it was entered wrong */
uint8 g_numWrongAttempts = 0;
uint8 g_numLocks = 0;
uint8 g_first_time = 0;

uint8 numOfUsedAuthMethods = 3;

uint8 (*authArray[numOfAvAuthMethods])(void) = {passwordAuth, rfidAuth, faceAuth};

/*******************************************************************************
 *                       	  Functions Definitions                            *
 *******************************************************************************/

void disableFuelPump(){
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_LOW);
    Timer0_Stop();
}

void enableFuelPump(){
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_HIGH);
}

void toggleFuelPump(){
    Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}

void changeAuthOption(uint8 opt){
    numOfUsedAuthMethods = opt;
    EEPROM_writeByte(NO_AUTH_USED_ADDRESS, numOfUsedAuthMethods);
    Delay_ms(5);
}


/* 
External Interrupt
*/
void tSwitch_Init(){
    GPIO_PORTF_IS_REG &= ~(1 << 4);      /* PF4 detect edges */
    GPIO_PORTF_IBE_REG |= (1 << 4);      /* PF4 will detect a certain edge */
    GPIO_PORTF_ICR_REG |= (1 << 4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
    GPIO_PORTF_IM_REG |= (1 << 4);       /* Enable Interrupt on PF4 pin */
    /* Set GPIO PORTF priotiy as 2 by set Bit number 22, 23 and 24 with value 2 */
    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY << GPIO_PORTF_PRIORITY_BITS_POS);
    NVIC_EN0_REG |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}

/* GPIO PORTF External Interrupt - ISR */
void GPIOPortF_Handler(void)
{
    /* Check for pin status */
    if(Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX)){
        if(Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX)){
            Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX, STD_HIGH);
        } else {
            Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX, STD_LOW);
        }
        Timer0_Init(); /* Reset the timer */
        Timer0_Stop(); /* Stop it */
    } else {
        Dio_WriteChannel(DioConf_LED2_CHANNEL_ID_INDEX, STD_LOW);
        Timer0_Init();
        Timer0_Start();
    }
    GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF0 (Interupt Flag) */
}

/*******************************************************************************************************
 * [Name]: Drivers_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible for Initializing of (MCAL) Drivers like UART & I2C and (HAL)
 * Drivers like GPS/GSM Modules and Enabling Global Interrupt (I-Bit) in Control Block.
 ********************************************************************************************************/
void Drivers_Init(void)
{
    Port_Init(&Port_Configuration);
    Dio_Init(&Dio_Configuration);
    Uart_Init(&Uart_Configuration);
    tSwitch_Init();
    I2c_Init(&I2c_Confiuration);
    GPS_init();
    GSM_init();
    Timer1_setCallBack(GPS_updateLocation);
    Timer1_Init();
    Timer0_setCallBack(disableFuelPump);
    Timer0_Init();
    Timer0_Stop();
    
    systemOffSetCallBackPtr(disableFuelPump);
    systemOnSetCallBackPtr(enableFuelPump);
    changeAuthOptSetCallBackPtr(changeAuthOption);
    /* We need a basic NVIC driver */
    NVIC_PRI14_REG = (NVIC_PRI14_REG & UART3_PRIORITY_MASK) | (UART3_PRIORITY_LEVEL<<UART3_PRIORITY_BITS_POS);
    NVIC_PRI5_REG = (NVIC_PRI5_REG & TIMER1A_PRIORITY_MASK) | (TIMER1A_PRIORITY_LEVEL<<TIMER1A_PRIORITY_BITS_POS);
    NVIC_PRI4_REG = (NVIC_PRI4_REG & TIMER0A_PRIORITY_MASK) | (TIMER0A_PRIORITY_LEVEL<<TIMER0A_PRIORITY_BITS_POS);
    NVIC_EN1_REG |= (1<<27);
    NVIC_EN0_REG |= (1<<21);
    NVIC_EN0_REG |= (1<<19);
    Enable_Interrupts();
}


int main(void){
    uint8 option = 0;
    uint8 otpCode[10];
    Drivers_Init();
    EEPROM_readByte(NO_AUTH_USED_ADDRESS, &numOfUsedAuthMethods);
    while(1){
        /* Read the EEPROM address for first time use */
        EEPROM_readByte(FIRST_TIME_ADDRESS, &g_first_time);

        EEPROM_readByte(WRONG_ATTEMPTS_ADDRESS, &g_numWrongAttempts);

        if (g_first_time == 0xFF) {
            systemSetup();
        }
        else {
            Uart_SendByte(HMI_BLOCK_UART, DISPLAY_OPTIONS_CMD);
            option = Uart_ReceiveByte(HMI_BLOCK_UART);
            switch (option)
            {
            case 1:
                if (systemAuth()) {
                    /* OUTPUT 1 to a pin */
                    /* Do in a function later plz */
                    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_HIGH);
                    Uart_SendByte(HMI_BLOCK_UART, ACCESS_GRANTED_CMD);
                }
                break;
            case 2:
                if (systemAuth()) {
                    passwordSetup();
                    Uart_SendByte(HMI_BLOCK_UART, PASSWORD_CHANGED_CMD);
                }
                break;
            case 3:
                if (systemAuth()) {
                    resetCredentials();
                    Uart_SendByte(HMI_BLOCK_UART, SYSTEM_RESET_CREDENTIALS_CMD);
                    Delay_ms(3000);
                }
                break;
            case 4:
                Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_LOW);
                EEPROM_writeByte(FIRST_TIME_ADDRESS, 0xFF);
                Delay_ms(10);
                EEPROM_writeByte(WRONG_ATTEMPTS_ADDRESS, 0);
                Delay_ms(10);
                break;
            default:
                break;
            }
        }

    }
}



void systemSetup(void){
    Uart_SendByte(HMI_BLOCK_UART, FIRST_TIME_CMD);
    passwordSetup();
    rfidSetup();
    faceSetup();
    
    /* Send setup complete command to HMI */
    Uart_SendByte(HMI_BLOCK_UART, SETUP_COMPLETE_CMD);

    /* Change first time to 0x00 to indicate that this is not the first time when reset occurs */
    EEPROM_writeByte(FIRST_TIME_ADDRESS, 0x00);
    Delay_ms(5);
    EEPROM_writeByte(NO_AUTH_USED_ADDRESS, 3);
    Delay_ms(5);
}

void passwordSetup(void){
    uint8 pass1[PASSWORD_LENGTH];
    uint8 pass2[PASSWORD_LENGTH];
    
    uint8 uidCounter = 0;
    boolean isMatch = TRUE;

    do{
        isMatch = TRUE;
        /* send setup password command to HMI */
        Uart_SendByte(HMI_BLOCK_UART, SETUP_PASSWORD_CMD);

        /* Get the 1st password from HMI */
        for(uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++){
            pass1[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
            Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
        }

        /* Get the 2nd password from HMI */
        for (uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++) {
            pass2[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
            Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
        }

        /* Check if the two passwords match each other */
        for(uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++){
            if(pass1[uidCounter] != pass2[uidCounter]){
                isMatch = FALSE;
                Uart_SendByte(HMI_BLOCK_UART, PASSWORD_MISSMATCH_CMD);
                break;
            }
        }
    } while(isMatch == FALSE); /* Loop until the two passwords match each other */

    /* save the password into the EEPROM */
    for (uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++) {
        EEPROM_writeByte(PASSWORD_ADDRESS + uidCounter, pass1[uidCounter]);
        Delay_ms(5);
    }
} /* end of passwordSetup function */


void rfidSetup(void){
    /* Array to hold the value of the unique id of the rfid tag */
    uint8 rfidTag1[RFID_UNIQUE_ID_LENGTH];
    uint8 rfidTag2[RFID_UNIQUE_ID_LENGTH];
    
    /* A counter to loop through the array of the uid */
    uint8 uidCounter = 0;

    /* send setup rfid command to HMI */
    Uart_SendByte(HMI_BLOCK_UART, SETUP_RFID_CMD);
    
    /* get the 1st rfid uid from HMI */
    for(uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++){
        rfidTag1[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
        Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
    }
    
    /* get the 2nd rfid uid from HMI */
    for (uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++) {
        rfidTag2[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
        Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
    }

    /* Save the 1st unique RFID to the EEPROM */
    for(uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++){
        EEPROM_writeByte(RFID_ADDRESS + uidCounter, rfidTag1[uidCounter]);
        Delay_ms(5);
    }

    /* Save the 2nd unique RFID to the EEPROM */
    for(uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++){
        EEPROM_writeByte(RFID_ADDRESS + RFID_UNIQUE_ID_LENGTH + uidCounter, rfidTag2[uidCounter]);
        Delay_ms(5);
    }
} /* end of rfidSetup function */

void faceSetup(void){
    /* A variable to hold the response on the image taken from the raspberry pi */
    uint8 faceResponse = 0;
    /* Send look at camera command to the HMI to envoke the user to look at the user */
    Uart_SendByte(HMI_BLOCK_UART, LOOK_AT_CAMERA_CMD);
    Delay_ms(3000);

    do{
        /* Send first time command to raspberry pi */
        Uart_SendByte(RASPBERRY_PI_UART, RASP_FIRST_TIME_CMD);
        /* Get the response from raspberry pi */
        faceResponse = Uart_ReceiveByte(RASPBERRY_PI_UART);
        
        if(faceResponse != RASP_SETUP_SUCCEEDED_REPORT){
            Uart_SendByte(HMI_BLOCK_UART, FACE_SETUP_FAILED_CMD);
            Uart_SendByte(HMI_BLOCK_UART, LOOK_AT_CAMERA_CMD);
            Delay_ms(1000);
        }
    } while(faceResponse != RASP_SETUP_SUCCEEDED_REPORT); /* Loop until a valid response */
}

boolean systemAuth(void){
    uint8 authCounter = 0;
    uint8 otpCode[OTP_LENGTH+1] = {0};
    otpCode[OTP_LENGTH] = '\0';
    uint8 otpMessage[OTP_LENGTH+20] = "OTP: ";
    uint8 HMI_OTP[OTP_LENGTH];
    uint8 uidCounter = 0;
    boolean isMatch = TRUE;

    for(authCounter = 0; authCounter < numOfUsedAuthMethods; authCounter++){
        g_numWrongAttempts = 0;
        if((*authArray[authCounter])() == FALSE){
            g_numLocks++;
            if(g_numLocks >= MAX_NUMBER_OF_LOCKS){
                generateOTP(otpCode, OTP_LENGTH);
                strcat(otpMessage, otpCode);

                GPS_updateLocation();

                NVIC_EN1_REG &= ~(1 << 27);
                GSM_sendSmsToUser(otpMessage);
                NVIC_EN1_REG |= (1 << 27);

                Uart_SendByte(HMI_BLOCK_UART, OTP_CMD);
                for (uidCounter = 0; uidCounter < OTP_LENGTH; uidCounter++) {
                    HMI_OTP[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
                    if(HMI_OTP[uidCounter] >= 0 && HMI_OTP[uidCounter] <= 9) HMI_OTP[uidCounter] = HMI_OTP[uidCounter] + '0';
                    Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
                }

                for (uidCounter = 0; uidCounter < OTP_LENGTH; uidCounter++) {
                    if (HMI_OTP[uidCounter] != otpCode[uidCounter]) {
                        isMatch = FALSE;
                        break;
                    }
                }
                if(isMatch != TRUE){
                    Uart_SendByte(HMI_BLOCK_UART, WRONG_OTP_CMD);
                    Delay_ms(30000);
                }
                g_numLocks = 0;
                return FALSE;
            } else {
                Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX, STD_LOW);
                Uart_SendByte(HMI_BLOCK_UART, LOCK_CMD);
                GPS_updateLocation();
                NVIC_EN1_REG &= ~(1 << 27);
                GSM_sendSmsToUser("Access Attempt - Vehicle");
                NVIC_EN1_REG |= (1 << 27);
                Delay_ms(LOCK_TIME);
                return FALSE;
            }
        }
    }
    g_numLocks = 0;
    return TRUE;
}



uint8 passwordAuth(void){
    uint8 hmiPass[PASSWORD_LENGTH];
    uint8 eepromPass[PASSWORD_LENGTH];

    uint8 uidCounter = 0;

    boolean isMatch = TRUE;

    do{
        isMatch = TRUE;
        Uart_SendByte(HMI_BLOCK_UART, GET_PASSWORD_CMD);
        for (uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++) {
            hmiPass[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
            Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
        }

        for (uidCounter = 0; uidCounter < PASSWORD_LENGTH; uidCounter++) {
            EEPROM_readByte(PASSWORD_ADDRESS + uidCounter, &eepromPass[uidCounter]);
            if (eepromPass[uidCounter] != hmiPass[uidCounter]) {
                isMatch = FALSE;
                break;
            }
        }

        if(isMatch == FALSE){
            Uart_SendByte(HMI_BLOCK_UART, WRONG_PASSWORD_CMD);
            g_numWrongAttempts++;
            if(g_numWrongAttempts >= MAX_NUMBER_OF_FAILED_ATTEMPTS){
                return FALSE;
            }
        }
    } while(isMatch == FALSE);

    return TRUE;
}



uint8 rfidAuth(void){
    uint8 hmiRfid[RFID_UNIQUE_ID_LENGTH];
    uint8 eepromRfid1[RFID_UNIQUE_ID_LENGTH];
    uint8 eepromRfid2[RFID_UNIQUE_ID_LENGTH];

    uint8 uidCounter = 0;

    boolean isMatch = TRUE;

    do{
        isMatch = TRUE;
        Uart_SendByte(HMI_BLOCK_UART, GET_RFID_CMD);

        for (uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++) {
            hmiRfid[uidCounter] = Uart_ReceiveByte(HMI_BLOCK_UART);
            Uart_SendByte(HMI_BLOCK_UART, CONTINUE_CMD);
        }

        for (uidCounter = 0; uidCounter < RFID_UNIQUE_ID_LENGTH; uidCounter++) {
            EEPROM_readByte(RFID_ADDRESS + uidCounter, &eepromRfid1[uidCounter]);
            EEPROM_readByte(RFID_ADDRESS + RFID_UNIQUE_ID_LENGTH + uidCounter, &eepromRfid2[uidCounter]);

            if (( hmiRfid[uidCounter] != eepromRfid1[uidCounter] ) && ( hmiRfid[uidCounter] != eepromRfid2[uidCounter] )) {
                isMatch = FALSE;
                break;
            }
        }

        if(isMatch == FALSE){
            Uart_SendByte(HMI_BLOCK_UART, TAG_FAILED_CMD);
            g_numWrongAttempts++;
            if(g_numWrongAttempts >= MAX_NUMBER_OF_FAILED_ATTEMPTS){
                return FALSE;
            }
        }
    } while(isMatch == FALSE);

    return TRUE;
}



uint8 faceAuth(void){
    /* A variable to hold the response on the image taken from the raspberry pi */
    uint8 faceResponse = 0;
    /* Send look at camera command to the HMI to envoke the user to look at the user */
    Uart_SendByte(HMI_BLOCK_UART, LOOK_AT_CAMERA_CMD);
    Delay_ms(3000);

    do{
        /* Send first time command to raspberry pi */
        Uart_SendByte(RASPBERRY_PI_UART, RASP_AUTH_CMD);
        /* Get the response from raspberry pi */
        faceResponse = Uart_ReceiveByte(RASPBERRY_PI_UART);
        
        if(faceResponse != RASP_AUTH_SUCCESS_REPORT){
            Uart_SendByte(HMI_BLOCK_UART, FACE_SETUP_FAILED_CMD);
            Delay_ms(1000);
            g_numWrongAttempts++;
            if(g_numWrongAttempts >= MAX_NUMBER_OF_FAILED_ATTEMPTS){
                return FALSE;
            }
            Uart_SendByte(HMI_BLOCK_UART, LOOK_AT_CAMERA_CMD);
        }
    } while(faceResponse != RASP_AUTH_SUCCESS_REPORT); /* Loop until a valid response */

    return TRUE;
}

void resetCredentials(void){
    /* Change first time to 0xFF to indicate that this first time and restart credential setup */
    EEPROM_writeByte(FIRST_TIME_ADDRESS, 0xFF);
    Delay_ms(5);
}

void generateOTP(uint8* numbers, uint8 length){
    uint8 counter = 0;
    volatile uint8 generatedNumber = 0;
    for(counter = 0; counter < length; counter++){
        srand(Timer1_ReadValue());
        generatedNumber = rand() % 14;
        
        if(generatedNumber >= 0 && generatedNumber <= 9){
            numbers[counter] = generatedNumber + '0';
        } else {
            numbers[counter] = generatedNumber - 10 + 'A';
        }
    }
}