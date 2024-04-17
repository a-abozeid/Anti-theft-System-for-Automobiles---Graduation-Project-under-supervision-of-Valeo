/******************************************************************************
 *
 * Module: RFID
 *
 * File Name: RFID.c
 *
 * Description: Source File for RFID Module
 *
 * Created on: Feb 23, 2022
 *
 * Authors: Mourad Eldin Nash'at - Abdelaziz Abu Zaid
 *
 *******************************************************************************/


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include "RFID.h"
#include "Spi.h"
#include "Dio.h"

/*******************************************************************************
 *                       	  Functions Definitions                            *
 *******************************************************************************/

/*******************************************************************************
 * [Name]: RFID_Write
 * [Parameters]: uint8 address , uint8 value
 * [Return]: void (none)
 * [Description]: The Function responsible of writing to a certain
 * 				  MFRC522 register a byte of data
 *******************************************************************************/
void RFID_Write(uint8 address , uint8 value)
{
    Dio_WriteChannel(DioConf_SPI_SS_CHANNEL_ID_INDEX, STD_LOW);
    SPI_SendReceiveByte(RFID_SPI,(address<<1)&0x7E);
    SPI_SendReceiveByte(RFID_SPI, value);
    Dio_WriteChannel(DioConf_SPI_SS_CHANNEL_ID_INDEX, STD_HIGH);
}


/*******************************************************************************
 * [Name]: Read_RFID
 * [Parameters]: uint8 address
 * [Return]: a byte of data read from the register
 * [Description]: The Function responsible of reading From a certain MFRC522
 * 				  a byte of data register
 *******************************************************************************/
uint8 RFID_Read(uint8 address)
{
	uint8 data;	
    Dio_WriteChannel(DioConf_SPI_SS_CHANNEL_ID_INDEX, STD_LOW);
	SPI_SendReceiveByte(RFID_SPI,((address<<1)&0x7E)|0x80);
	data = SPI_SendReceiveByte(RFID_SPI, 0x00);
    Dio_WriteChannel(DioConf_SPI_SS_CHANNEL_ID_INDEX, STD_HIGH);
	return data;
}


/*******************************************************************************
 * [Name]: Set_BitMask
 * [Parameters]: uint8 reg , uint8 mask
 * [Return]: void (none)
 * [Description]: The Function responsible of Setting MFRC522 register bit
 *******************************************************************************/
void SetBitMask(uint8 reg , uint8 mask)
{
    uint8 tmp;
    tmp = RFID_Read(reg);
    RFID_Write(reg , tmp | mask);  // set bit mask
}


/*******************************************************************************
 * [Name]: Clear_BitMask
 * [Parameters]: uint8 reg , uint8 mask
 * [Return]: void (none)
 * [Description]: The Function responsible of clearing MFRC522 register bit
 *******************************************************************************/
void clearBitMask(uint8 reg , uint8 mask)
{
    uint8 tmp;
    tmp = RFID_Read(reg);
    RFID_Write(reg , tmp & (~mask));  // clear bit mask
}


/*******************************************************************************
 * [Name]: Antenna_On
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Opening antennas, each time you
 * 				  start or shut down the natural barrier between the transmitter
 * 				  should be at least 1ms interval
 *******************************************************************************/
void Antenna_On(void)
{
	SetBitMask(TxControlReg , 0x03);
}


/*******************************************************************************
 * [Name]: Antenna_Off
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of closing antennas, each time you
 * 				  start or shut down the natural barrier between the transmitter
 * 				  should be at least 1ms interval
 *******************************************************************************/
void Antenna_Off(void)
{
	clearBitMask(TxControlReg , 0x03);
}


/*******************************************************************************
 * [Name]: RFID_Request
 * [Parameters]: uint8 req_mode , uint8 * tag_type
 * [Return]: uint8
 * [Description]: The Function responsible for Finding cards and reading
 * 				  the card type number
 *******************************************************************************/
uint8 RFID_Request(uint8 req_mode, uint8 * tag_type)
{
	uint8 status;
	uint32 back_bits; // The received data bits

	RFID_Write(BitFramingReg , 0x07);   // TxLastBists = BitFramingReg[2..0]

	tag_type[0] = req_mode;

	status = RFID_To_Card(TRANSCEIVE , tag_type, 1 , tag_type , &back_bits);
	if ((status != CARD_FOUND) || (back_bits != 0x10))
	{
		status = ERROR;
	}

	return status;
}


/*******************************************************************************
 * [Name]: RFID_To_Card
 * [Parameters]: uint8 command , uint8 *send_data , uint8 send_data_len ,
 * 				 uint8 *back_data , uint32 *back_data_len
 * [Return]: uint8
 * [Description]: The Function responsible for RC522 and ISO14443 card communication
 *******************************************************************************/
uint8 RFID_To_Card(uint8 command, uint8 *send_data, uint8 send_data_len, uint8
		*back_data, uint32 *back_data_len)
{
	/* Initial Status */
	uint8 status = ERROR;

	uint8 irqEn = 0x00;
	uint8 waitIRq = 0x00;
	uint8 lastBits;
	uint8 n;
	/* Loop Counter */
	uint32 i;

	switch (command)
	{
	case MF_AUTHENT:     // Certification cards close
	{
		irqEn = 0x12;
		waitIRq = 0x10;
		break;
	}
	case TRANSCEIVE:  // Transmit FIFO data
	{
		irqEn = 0x77;
		waitIRq = 0x30;
		break;
	}
	default:
		break;
	}

	RFID_Write(ComIEnReg , irqEn |0x80);  // Interrupt request
	clearBitMask(ComIrqReg , 0x80);         // Clear all interrupt request bit
	SetBitMask(FIFOLevelReg, 0x80);         // FlushBuffer=1, FIFO Initialization

	RFID_Write(CommandReg , IDLE);    // NO action; Cancel the current command

	// Writing data to the FIFO
	for (i = 0; i < send_data_len; i++)
	{
		RFID_Write(FIFODataReg, send_data[i]);
	}

	// Execute the command
	RFID_Write(CommandReg , command);
	if (command == TRANSCEIVE)
	{
		SetBitMask(BitFramingReg, 0x80);      // StartSend=1,transmission of data starts
	}

	// Waiting to receive data to complete
	i = 2000;	// i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
	do
	{
		// CommIrqReg[7..0]
		// Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = RFID_Read(ComIrqReg);
		i--;
	}
	while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	clearBitMask(BitFramingReg, 0x80);      // StartSend=0

	if (i != 0)
	{
		if(!(RFID_Read(ErrorReg) & 0x1B))  // BufferOvfl Collerr CRCErr ProtecolErr
		{
			status = CARD_FOUND;
			if (n & irqEn & 0x01)
			{
				status = CARD_NOT_FOUND;             // ??
			}

			if (command == TRANSCEIVE)
			{
				n = RFID_Read(FIFOLevelReg);
				lastBits = RFID_Read(ControlReg) & 0x07;
				if (lastBits)
				{
					*back_data_len = (n-1)*8 + lastBits;
				}
				else
				{
					*back_data_len = n*8;
				}

				if (n == 0)
				{
					n = 1;
				}
				if (n > RFID_UNIQUE_ID_LENGTH)
				{
					n = RFID_UNIQUE_ID_LENGTH;
				}

				// Reading the received data in FIFO
				for (i=0; i<n; i++)
				{
					back_data[i] = RFID_Read(FIFODataReg);
				}
			}
		}
		else {
			//printf("~~~ buffer overflow, collerr, crcerr, or protecolerr\r\n");
			status = ERROR;
		}
	}
	else {
		//printf("~~~ request timed out\r\n");
	}

	return status;

}


/*******************************************************************************
 * [Name]: RFID_Reset
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Resetting The MFRC522 RFID Module
 *******************************************************************************/
void RFID_Reset(void)
{
	RFID_Write(CommandReg , SOFT_RESET);
}


/*******************************************************************************
 * [Name]: RFID_Init
 * [Parameters]: void (none)
 * [Return]: void (none)
 * [Description]: The Function responsible of Initializing The MFRC522 RFID Module
 *******************************************************************************/
void RFID_Init(void)
{
	uint8 byte;
	RFID_Reset();
	RFID_Write(TModeReg, 0x8D);
    RFID_Write(TPrescalerReg, 0x3E);
    RFID_Write(TReloadRegH, 30);   
    RFID_Write(TReloadRegL, 0);	
	RFID_Write(TxASKReg, 0x40);	
	RFID_Write(ModeReg, 0x3D);

	byte = RFID_Read(TxControlReg);
	if(!(byte & 0x03))
	{
		RFID_Write(TxControlReg , byte | 0x03);
	}

	// turn antenna on
	Antenna_On();
}


uint8 RFID_getCardSerial(uint8 * serial_out)
{
	uint8 status;
    uint8 i;
	uint8 serNumCheck=0;
    uint32 unLen;
    
	RFID_Write(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
 
    serial_out[0] = PICC_ANTICOLL;
    serial_out[1] = 0x20;
    status = RFID_To_Card(Transceive_CMD, serial_out, 2, serial_out, &unLen);

    if (status == CARD_FOUND)
	{
		//Check card serial number
		for (i=0; i<4; i++)
		{   
		 	serNumCheck ^= serial_out[i];
		}
		if (serNumCheck != serial_out[i])
		{   
			status = ERROR;    
		}
    }
    return status;
}
