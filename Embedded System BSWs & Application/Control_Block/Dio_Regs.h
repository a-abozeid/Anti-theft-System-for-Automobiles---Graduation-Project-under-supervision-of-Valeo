 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver Registers
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef DIO_REGS_H
#define DIO_REGS_H

#include "Std_Types.h"

#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))


#define GPIO_PORT_NUMS (6U) /* Number of GPIO ports in TM4C123GH6PM Microcontroller */

/* PORTA */
#define GPIO_PORTA_ID               (0U) /* PORTA ID 0 */

#define GPIO_PA0                    (0U) /* PINA 0 */
#define GPIO_PA1                    (1U) /* PINA 1 */
#define GPIO_PA2                    (2U) /* PINA 2 */
#define GPIO_PA3                    (3U) /* PINA 3 */
#define GPIO_PA4                    (4U) /* PINA 4 */
#define GPIO_PA5                    (5U) /* PINA 5 */
#define GPIO_PA6                    (6U) /* PINA 6 */
#define GPIO_PA7                    (7U) /* PINA 7 */

/* PORTB */
#define GPIO_PORTB_ID               (1U) /* PORTB ID 1 */

#define GPIO_PB0                    (0U) /* PINB 0 */
#define GPIO_PB1                    (1U) /* PINB 1 */
#define GPIO_PB2                    (2U) /* PINB 2 */
#define GPIO_PB3                    (3U) /* PINB 3 */
#define GPIO_PB4                    (4U) /* PINB 4 */
#define GPIO_PB5                    (5U) /* PINB 5 */
#define GPIO_PB6                    (6U) /* PINB 6 */
#define GPIO_PB7                    (7U) /* PINB 7 */

/* PORTC */
#define GPIO_PORTC_ID               (2U) /* PORTC ID 2 */

#define GPIO_PC0                    (0U) /* PINC 0 */
#define GPIO_PC1                    (1U) /* PINC 1 */
#define GPIO_PC2                    (2U) /* PINC 2 */
#define GPIO_PC3                    (3U) /* PINC 3 */
#define GPIO_PC4                    (4U) /* PINC 4 */
#define GPIO_PC5                    (5U) /* PINC 5 */
#define GPIO_PC6                    (6U) /* PINC 6 */
#define GPIO_PC7                    (7U) /* PINC 7 */

/* PORTD */
#define GPIO_PORTD_ID               (3U) /* PORTD ID 3 */

#define GPIO_PD0                    (0U) /* PIND 0 */
#define GPIO_PD1                    (1U) /* PIND 1 */
#define GPIO_PD2                    (2U) /* PIND 2 */
#define GPIO_PD3                    (3U) /* PIND 3 */
#define GPIO_PD4                    (4U) /* PIND 4 */
#define GPIO_PD5                    (5U) /* PIND 5 */
#define GPIO_PD6                    (6U) /* PIND 6 */
#define GPIO_PD7                    (7U) /* PIND 7 */

/* PORTE */
#define GPIO_PORTE_ID               (4U) /* PORTE ID 4 */

#define GPIO_PE0                    (0U) /* PINE 0 */
#define GPIO_PE1                    (1U) /* PINE 1 */
#define GPIO_PE2                    (2U) /* PINE 2 */
#define GPIO_PE3                    (3U) /* PINE 3 */
#define GPIO_PE4                    (4U) /* PINE 4 */
#define GPIO_PE5                    (5U) /* PINE 5 */
#define GPIO_PE6                    (6U) /* PINE 6 */
#define GPIO_PE7                    (7U) /* PINE 7 */

/* PORTF */
#define GPIO_PORTF_ID               (5U) /* PORTF ID 5 */

#define GPIO_PF0                    (0U) /* PINF 0 */
#define GPIO_PF1                    (1U) /* PINF 1 */
#define GPIO_PF2                    (2U) /* PINF 2 */
#define GPIO_PF3                    (3U) /* PINF 3 */
#define GPIO_PF4                    (4U) /* PINF 4 */
#define GPIO_PF5                    (5U) /* PINF 5 */
#define GPIO_PF6                    (6U) /* PINF 6 */
#define GPIO_PF7                    (7U) /* PINF 7 */



#endif /* DIO_REGS_H */
