 /******************************************************************************
 *
 * Module: lcd
 *
 * File Name: lcd.h
 *
 * Description: Header file for LCD driver
 *
 * Author: Hazem Youssery
 ******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "Dio.h"
#include "lcd_cfg.h"
/*
==============================================================================
*                              LCD Definitions 
==============================================================================
*/
/* LCD Data Port */
#define LCD_DATA_PORT DioConf_LCD_PORT_NUM  
/* Control Pins */
#define LCD_RS  DioConf_LCD_RS_CHANNEL_ID_INDEX
#define LCD_RW  DioConf_LCD_RW_CHANNEL_ID_INDEX
#define LCD_EN  DioConf_LCD_EN_CHANNEL_ID_INDEX

#if (LCD_DATA_BITS_MODE == LCD_FOUR_BIT_MODE)
#define LCD_PTR DioConf_LCD_GRP_PTR
#endif

/*
==============================================================================
*                              LCD Commands 
==============================================================================
*/
#define CLEAR_DISPLAY_SCREEN                            (0x01)
#define RETURN_HOME                                     (0x02)
#define SHIFT_CURSOR_TO_LEFT                            (0x04)
#define SHIFT_DISPLAY_RIGHT                             (0x05)
#define SHIFT_CURSOR_TO_RIGHT                           (0x06)
#define SHIFT_DISPLAY_LEFT                              (0x07)
#define DISPLAY_OFF_CURSOR_OFF                          (0x08)
#define DISPLAY_OFF_CURSOR_ON                           (0x0A)
#define DISPLAY_ON_CURSOR_OFF                           (0x0C)
#define DISPLAY_ON_CURSOR_ON                            (0x0E)
#define DISPLAY_ON_CURSOR_BLINKING                      (0x0F)
#define SHIFT_CURSOR_POSITION_TO_LEFT                   (0x10)
#define SHIFT_CURSOR_POSITION_TO_RIGHT                  (0x14)
#define SHIFT_ENTIRE_DISPLAY_TO_LEFT                    (0x18)
#define SHIFT_ENTIRE_DISPLAY_TO_RIGHT                   (0x1C)
#define LCD_SET_CURSOR_LOCATION                         (0x80)
#define FORCE_CURSOR_TO_BEGINNING_OF_SECOND_LINE        (0xC0)
#define LCD_TWO_LINES_EIGHT_BITS_MODE                   (0x38)
#define LCD_TWO_LINES_FOUR_BITS_MODE                    (0x28)


/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/

/**************************************************************************************
 * [Function Name]:  LCD_init
 * [Args]: void
 * [Returns]: void
 * [Description]: initialize the LCD with the working mode
 **************************************************************************************/
void LCD_init(void);

/**************************************************************************************
 * [Function Name]: LCD_sendCommand
 * [Args]: uint8 command: the command to be sent to the LCD
 * [Returns]: void
 * [Description]: this function is responsible for sending a command to LCD
 **************************************************************************************/
void LCD_sendCommand(uint8 command);

/**************************************************************************************
 * [Function Name]:  LCD_displayCharacter
 * [Args]: uint8 data, the character to be displayed on the lcd
 * [Returns]: void
 * [Description] this function is responsible for displaying a character on the LCD
 **************************************************************************************/
void LCD_displayCharacter(uint8 data);

/**************************************************************************************
 * [Function Name] LCD_displayString
 * [Args]: uint8 * str Pointer to string
 * [Returns]: void
 * [Description]: this function is responsible for displaying string so it takes 
 *                a pointer to this string and loop on it's characters.
 **************************************************************************************/
void LCD_displayString(uint8 *str);

/**************************************************************************************
 * [Function Name]: LCD_moveCursor
 * [Args]: uint8 row, uint8 col
 * [Returns]: void
 * [Description]: Jump to a specific location on the LCD
 **************************************************************************************/
void LCD_moveCursor(uint8 row,uint8 col);

/**************************************************************************************
 * [Function Name]: LCD_displayStringRowColumn
 * [Args]:uint8 row: the row on the LCD to jump to
 *        uint8 col: the column on the LCD to jump to
 *        uint8 *str: a pointer to the string to be displayed
 * [Returns]: void
 * [Description]: Jump to a specific location on the LCD and display a string 
 **************************************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* data);

/**************************************************************************************
 * [Function Name]: LCD_clearScreen
 * [Args]: void
 * [Returns]: void
 * [Description]: A function to clear the LCD
 **************************************************************************************/
void LCD_clearScreen(void);

/**************************************************************************************
 * [Function Name]: LCD_integerToString
 * [Args]: sint32 a_numberToDisplay: number that would be displayed on the LCD
 * [Returns]: void
 * [Description]: Display an integer on the LCD
 ***************************************************************************************/
void LCD_displayInteger(sint32 a_numberToDisplay);

void LCD_displayHex(uint8 number);

#endif /* LCD_H_ */
