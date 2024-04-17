 /******************************************************************************
 *
 * Module: lcd
 *
 * File Name: lcd.c
 *
 * Description: source file for LCD driver
 *
 * Author: Hazem Youssery
 ******************************************************************************/

/*
==============================================================================
*                                 Includes
==============================================================================
*/
#include "lcd.h" 
#include "sw_delay.h"
/*
==============================================================================
*                                Functions Code 
==============================================================================
*/

/**************************************************************************************
 * [Function Name]:  LCD_init
 * [Args]: void
 * [Returns]: void
 * [Description]: initialize the LCD with the working mode
 **************************************************************************************/
void LCD_init(void)
{
	
#if (LCD_DATA_BITS_MODE == LCD_FOUR_BIT_MODE)
    /* configure the LCD to be used in 4 bits mode */ 
	LCD_sendCommand(RETURN_HOME);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */

#elif (LCD_DATA_BITS_MODE == LCD_EIGHT_BIT_MODE)
    /* configure the LCD to be used in 8 bits mode */ 
    LCD_sendCommand(RETURN_HOME);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* initialize the LCD 8 bit mode*/
#endif
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);  /* Display ON and Cursor OFF */
	LCD_sendCommand(CLEAR_DISPLAY_SCREEN);   /* Clear the LCD */
}

/**************************************************************************************
 * [Function Name]: LCD_sendCommand
 * [Args]: uint8 command: the command to be sent to the LCD
 * [Returns]: void
 * [Description]: this function is responsible for sending a command to LCD
 **************************************************************************************/
void LCD_sendCommand(uint8 command)
{
#if(LCD_DATA_BITS_MODE == 4)
    /* Send the Higher Nibble */
	Dio_WriteChannelGroup(LCD_PTR,(command>>4)); 

    /* Writing Sequence */
	Dio_WriteChannel(LCD_RS,STD_LOW); /* Clear RS to select command register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear RW to write to the LCD */

    /* Send a pulse of HIGH to LOW on EN pin with a delay of 1 ms */
    Dio_WriteChannel(LCD_EN,STD_HIGH); 	/* Set EN */
	Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW);  /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */

    /* Send the Lower Nibble */
	Dio_WriteChannelGroup(LCD_PTR,command);

    /* Writing Sequence */
    Dio_WriteChannel(LCD_RS,STD_LOW);  /* Clear RS to select command register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear RW to write to the LCD */

    /* Send a pulse of HIGH to LOW on EN pin with a delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_HIGH); /* Set EN */
	Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW); /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */

#elif(LCD_DATA_BITS_MODE == LCD_EIGHT_BIT_MODE)
	/* send the command to the LCD data pins */
    Dio_WritePort(LCD_DATA_PORT,command);

    /* Writing Sequence */
	Dio_WriteChannel(LCD_RS,STD_LOW); /* Clear RS to select command register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear Rw to write to the LCD */
        
    /* Send a pulse of high to low */
	Dio_WriteChannel(LCD_EN,STD_HIGH); /* Set EN */
    Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW); /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */
#endif
}

/**************************************************************************************
 * [Function Name]:  LCD_displayCharacter
 * [Args]: uint8 data, the character to be displayed on the lcd
 * [Returns]: void
 * [Description] this function is responsible for displaying a character on the LCD
 **************************************************************************************/
void LCD_displayCharacter(uint8 data)
{
#if(LCD_DATA_BITS_MODE == 4)
    /* Send the Higher Nibble */
    Dio_WriteChannelGroup(LCD_PTR,(data>>4));

    /* Writing Sequence */
	Dio_WriteChannel(LCD_RS,STD_HIGH); /* Set RS to select data register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear RW to write to the LCD */
	
    /* Send a pulse of HIGH to LOW on EN pin with a delay of 1 ms */
    Dio_WriteChannel(LCD_EN,STD_HIGH); /* Set EN */
	Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW); /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */
    
    /* Send the Lower Nibble */
	Dio_WriteChannelGroup(LCD_PTR,data);

    /* Writing Sequence */
	Dio_WriteChannel(LCD_RS,STD_HIGH); /* Set RS to select data register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear RW to write to the LCD */

    /* Send a pulse of HIGH to LOW on EN pin with a delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_HIGH); /* Set EN */
	Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW); /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */
#elif(LCD_DATA_BITS_MODE == 8)

    /* Send the data (character) to the LCD data pins */
	Dio_WritePort(LCD_DATA_PORT,data);

	/* Writing Sequence */
	Dio_WriteChannel(LCD_RS,STD_HIGH); /* Set RS to select data register */
	Dio_WriteChannel(LCD_RW,STD_LOW); /* Clear RW to write to the LCD */
	
    /* Send a pulse of HIGH to LOW on EN pin with a delay of 1 ms */
    Dio_WriteChannel(LCD_EN,STD_HIGH); /* Set EN */
	Delay_ms(1); /* A short delay of 1 ms */
	Dio_WriteChannel(LCD_EN,STD_LOW); /* Clear EN */
	Delay_ms(1); /* A short delay of 1 ms */
	#endif
}
/**************************************************************************************
 * [Function Name] LCD_displayString
 * [Args]: uint8 * str Pointer to string
 * [Returns]: void
 * [Description]: this function is responsible for displaying string so it takes 
 *                a pointer to this string and loop on it's characters.
 **************************************************************************************/
void LCD_displayString (uint8 *str)
{
	uint8 i = 0;          /* variable to hold the count in the string */
	while(str[i]!='\0') /* till we reach the null character */
	{
		LCD_displayCharacter(str[i]); /* display the string char by char */
		i++;
	}
}

/**************************************************************************************
 * [Function Name]: LCD_moveCursor
 * [Args]: uint8 row, uint8 col
 * [Returns]: void
 * [Description]: Jump to a specific location on the LCD
 **************************************************************************************/
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address; /* to hold memory address of the target cursor location */

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0:
		lcd_memory_address=col;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x14;
		break;
	case 3:
		lcd_memory_address=col+0x54;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}





/**************************************************************************************
 * [Function Name]: LCD_clearScreen
 * [Args]: void
 * [Returns]: void
 * [Description]: A function to clear the LCD
 **************************************************************************************/
void LCD_clearScreen(void)
{ 
    /* send clear command to the LCD */
	LCD_sendCommand(CLEAR_DISPLAY_SCREEN);
}

/**************************************************************************************
 * [Function Name]: LCD_displayStringRowColumn
 * [Args]:uint8 row: the row on the LCD to jump to
 *        uint8 col: the column on the LCD to jump to
 *        uint8 *str: a pointer to the string to be displayed
 * [Returns]: void
 * [Description]: Jump to a specific location on the LCD and display a string 
 **************************************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8 *str)
{
	uint8 i = 0; /* A variable used to loop through the string */
	LCD_moveCursor(row,col); /* Move to a specific location on the LCD */

	while(str[i]!='\0')
	{
		LCD_displayCharacter(str[i]); /* Display the string character by character */
		i++;
	}
}

/**************************************************************************************
 * [Function Name]: LCD_integerToString
 * [Args]: sint32 a_numberToDisplay: number that would be displayed on the LCD
 * [Returns]: void
 * [Description]: Display an integer on the LCD
 ***************************************************************************************/
void LCD_displayInteger(sint32 a_numberToDisplay)
{
    /* Why 12?
     * The largest number in a signed number of 32 bits is 2,147,483,647 = 10 numbers
     * and the lowest number is -2,147,483,648 -> 10 numbers + 1 for the sign = 11 numbers
     * and if we add the string terminator we have 12 number(buffer size)     
     */
    uint8 buffer[12];

    uint8 counter = 0, i = 0;

    if(a_numberToDisplay == 0){
        /* display zero on the LCD */
        LCD_displayCharacter('0');
        /* Exit from the function by returning */
        return;
    } else if(a_numberToDisplay < 0){
        /* in case of negative number */
        
        /* Add the sign to the buffer */
        buffer[counter++] = '-';
        /* Make the number positive */
        a_numberToDisplay = -a_numberToDisplay;

        /* start i at 1 to leave the sign at reversing the number */
        i = 1;
    } 

    while(a_numberToDisplay != 0){
        /* Add the last digit in the number to the buffer */
        buffer[counter++] = (a_numberToDisplay % 10) + '0';

        /* Update the number after dividing by 10 */
        a_numberToDisplay /= 10;
    }

    /* Add the string terminator \0 to the buffer */
    buffer[counter--] = '\0';

    /* Now we need to reverse the number */
    for(;i < counter; i++, counter--){
        buffer[i] = buffer[i] ^ buffer[counter]; 
        buffer[counter] = buffer[i] ^ buffer[counter]; 
        buffer[i] = buffer[i] ^ buffer[counter]; 
    }
    /* Display the number */
    LCD_displayString(buffer);
}


void LCD_displayHex(uint8 number){
	uint8 byte = '0';

    uint8 valueToCheck = ((number>>4) & 0x0F);
    if(valueToCheck <= 9){
        byte = '0' + valueToCheck;
    } else {
        byte = 'A' + valueToCheck - 0x0A;
    }
    LCD_displayCharacter(byte);


    valueToCheck = number & 0x0F;
    if(valueToCheck <= 9){
        byte = '0' + valueToCheck;
    } else {
        byte = 'A' + valueToCheck - 0x0A;
    }

    LCD_displayCharacter(byte);
}