 /******************************************************************************
 *
 * Module: lcd
 *
 * File Name: lcd_cfg.h
 *
 * Description: Pre-Compile Configuration Header file for LCD driver
 *
 * Author: Hazem Youssery
 ******************************************************************************/

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define LCD_FOUR_BIT_MODE (4u)
#define LCD_EIGHT_BIT_MODE (8u)

/* Choose between LCD_EIGHT_BIT_MODE and LCD_FOUR_BIT_MODE */

#define LCD_DATA_BITS_MODE LCD_FOUR_BIT_MODE

#endif /* LCD_CFG_H_ */