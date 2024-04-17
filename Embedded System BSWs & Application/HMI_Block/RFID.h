/******************************************************************************
 *
 * Module: RFID
 *
 * File Name: RFID.h
 *
 * Description: Header File for RFID Module
 *
 * Created on: Feb 23, 2022
 *
 * Authors: Mourad Eldin Nash'at - Abdelaziz Abu Zaid
 *
 *******************************************************************************/

#ifndef RFID_H_
#define RFID_H_


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "Std_Types.h"



/*******************************************************************************
 *                                Definitions                                 *
 *******************************************************************************/

/* Card Status */
#define CARD_FOUND			   (uint8)0
#define CARD_NOT_FOUND		   (uint8)1
#define ERROR				   (uint8)2

/* Array Max Length */
#define RFID_UNIQUE_ID_LENGTH    (8u)

/* MFRC522 Registers addresses in hexadecimal */
/* Page 0: Command and Status */
#define CommandReg          	(0x01)
#define ComIEnReg           	(0x02)
#define DivIEnReg           	(0x03)
#define ComIrqReg           	(0x04)
#define DivIrqReg           	(0x05)
#define ErrorReg        	    (0x06)
#define Status1Reg       	    (0x07)
#define Status2Reg       	    (0x08)
#define FIFODataReg      	    (0x09)
#define FIFOLevelReg      	  	(0x0A)
#define WaterLevelReg      	 	(0x0B)
#define ControlReg          	(0x0C)
#define BitFramingReg      	 	(0x0D)
#define CollReg             	(0x0E)

/* Page 1: Command */
#define ModeReg           	    (0x11)
#define TxModeReg          	   	(0x12)
#define RxModeReg             	(0x13)
#define TxControlReg          	(0x14)
#define TxASKReg              	(0x15)
#define TxSelReg              	(0x16)
#define RxSelReg              	(0x17)
#define RxThresholdReg        	(0x18)
#define DemodReg              	(0x19)
#define MifareReg             	(0x1C)
#define SerialSpeedReg        	(0x1F)

/* Page 2: Configuration */
#define CRCResultRegM        	(0x21)
#define CRCResultRegL         	(0x22)
#define ModWidthReg           	(0x24)
#define RFCfgReg              	(0x26)
#define GsNReg                	(0x27)
#define CWGsCfgReg            	(0x28)
#define ModGsCfgReg           	(0x29)
#define TModeReg              	(0x2A)
#define TPrescalerReg         	(0x2B)
#define TReloadRegH           	(0x2C)
#define TReloadRegL           	(0x2D)
#define TCounterValueRegH     	(0x2E)
#define TCounterValueRegL     	(0x2F)

/* Page 3: Test Register */
#define TestSel1Reg           	(0x31)
#define TestSel2Reg           	(0x32)
#define TestPinEnReg          	(0x33)
#define TestPinValueReg       	(0x34)
#define TestBusReg            	(0x35)
#define AutoTestReg           	(0x36)
#define VersionReg            	(0x37)
#define AnalogTestReg         	(0x38)
#define TestDAC1Reg           	(0x39)
#define TestDAC2Reg           	(0x3A)
#define TestADCReg            	(0x3B)


/* MFRC522 Commands */
#define IDLE 					(0x00)  	   // NO action; Cancel the current command
#define MEM						(0x01) 		   // Stores 25 byte into the internal buffer
#define GENERATE_RANDOM_ID		(0x02)		   // Generate a 10 byte random ID Number
#define CALC_CRC				(0x03)  	   // CRC Calculate
#define TRANSMIT 				(0x04) 		   // Transmit data
#define NO_CMD_CHANGE			(0x07)		   // No Command Change
#define RECEIVE					(0x08) 		   // Receive Data
#define TRANSCEIVE				(0x0C) 		   // Transmit and receive data,
#define MF_AUTHENT				(0x0E) 		   // Authentication Key
#define SOFT_RESET				(0x0F) 		   // Reset The Module


/* Mifare_One card command word */
# define PICC_REQIDL          	(0x26)         // find the antenna area does not enter hibernation
# define PICC_REQALL          	(0x52)         // find all the cards antenna area
# define PICC_ANTICOLL        	(0x93)         // anti-collision
# define PICC_SElECTTAG       	(0x93)         // election card
# define PICC_AUTHENT1A       	(0x60)         // authentication key A
# define PICC_AUTHENT1B       	(0x61)         // authentication key B
# define PICC_READ            	(0x30)         // Read Block
# define PICC_WRITE           	(0xA0)         // write block
# define PICC_DECREMENT       	(0xC0)         // debit
# define PICC_INCREMENT       	(0xC1)         // recharge
# define PICC_RESTORE         	(0xC2)         // transfer block data to the buffer
# define PICC_TRANSFER        	(0xB0)         // save the data in the buffer
# define PICC_HALT            	(0x50)         // Sleep





#define Idle_CMD 				0x00
#define Mem_CMD					0x01
#define GenerateRandomId_CMD	0x02
#define CalcCRC_CMD				0x03
#define Transmit_CMD			0x04
#define NoCmdChange_CMD			0x07
#define Receive_CMD				0x08
#define Transceive_CMD			0x0C
#define Reserved_CMD			0x0D
#define MFAuthent_CMD			0x0E
#define SoftReset_CMD			0x0F

/*******************************************************************************
 *                     		  Functions Prototypes                             *
 *******************************************************************************/

/*******************************************************************************
 * [Name]: RFID_Write
 * [Parameters]: uint8 address , uint8 value
 * [Return]: void (none)
 * [Description]: The Function responsible of writing to a certain
 * 				  MFRC522 register a byte of data
 *******************************************************************************/
void RFID_Write(uint8 address , uint8 value);


/*******************************************************************************
 * [Name]: Read_RFID
 * [Parameters]: uint8 address
 * [Return]: a byte of data read from the register
 * [Description]: The Function responsible of reading From a certain MFRC522
 * 				  a byte of data register
 *******************************************************************************/
uint8 RFID_Read(uint8 address);


/*******************************************************************************
 * [Name]: Set_BitMask
 * [Parameters]: uint8 reg , uint8 mask
 * [Return]: void (none)
 * [Description]: The Function responsible of Setting MFRC522 register bit
 *******************************************************************************/
void Set_BitMask(uint8 reg , uint8 mask);


/*******************************************************************************
 * [Name]: Clear_BitMask
 * [Parameters]: uint8 reg , uint8 mask
 * [Return]: void (none)
 * [Description]: The Function responsible of clearing MFRC522 register bit
 *******************************************************************************/
void Clear_BitMask(uint8 reg , uint8 mask);


/*******************************************************************************
 * [Name]: Antenna_On
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Opening antennas, each time you
 * 				  start or shut down the natural barrier between the transmitter
 * 				  should be at least 1ms interval
 *******************************************************************************/
void Antenna_On(void);


/*******************************************************************************
 * [Name]: Antenna_Off
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of closing antennas, each time you
 * 				  start or shut down the natural barrier between the transmitter
 * 				  should be at least 1ms interval
 *******************************************************************************/
void Antenna_Off(void);


/*******************************************************************************
 * [Name]: RFID_Request
 * [Parameters]: uint8 req_mode , uint8 * tag_type
 * [Return]: uint8
 * [Description]: The Function responsible for Finding cards and reading
 * 				  the card type number
 *******************************************************************************/
uint8 RFID_Request(uint8 req_mode, uint8 * tag_type);


/*******************************************************************************
 * [Name]: RFID_To_Card
 * [Parameters]: uint8 command , uint8 *send_data , uint8 send_data_len ,
 * 				 uint8 *back_data , uint32 *back_data_len
 * [Return]: uint8
 * [Description]: The Function responsible for RC522 and ISO14443 card communication
 *******************************************************************************/
uint8 RFID_To_Card(uint8 command, uint8 *send_data, uint8 send_data_len, uint8
		*back_data, uint32 *back_data_len);


/*******************************************************************************
 * [Name]: RFID_Reset
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Resetting The MFRC522 RFID Module
 *******************************************************************************/
void RFID_Reset(void);


/*******************************************************************************
 * [Name]: RFID_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Initializing The MFRC522 RFID Module
 *******************************************************************************/
void RFID_Init(void);

uint8 RFID_getCardSerial(uint8 * serial_out);

#endif /* RFID_H_ */
