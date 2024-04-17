 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver Registers
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef PORT_REGS_H
#define PORT_REGS_H

#include "Std_Types.h"

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           (0x40004000) /* PORTA Base Address */
#define GPIO_PORTB_BASE_ADDRESS           (0x40005000) /* PORTB Base Address */
#define GPIO_PORTC_BASE_ADDRESS           (0x40006000) /* PORTC Base Address */
#define GPIO_PORTD_BASE_ADDRESS           (0x40007000) /* PORTD Base Address */
#define GPIO_PORTE_BASE_ADDRESS           (0x40024000) /* PORTE Base Address */
#define GPIO_PORTF_BASE_ADDRESS           (0x40025000) /* PORTF Base Address */

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              (0x3FC) /* Data Register Offset */
#define PORT_DIR_REG_OFFSET               (0x400) /* Direction Register Offset */
#define PORT_ALT_FUNC_REG_OFFSET          (0x420) /* Alternative Function Register Offset */
#define PORT_PULL_UP_REG_OFFSET           (0x510) /* Pull-Up Register Offset */
#define PORT_PULL_DOWN_REG_OFFSET         (0x514) /* Pull-Down Register Offset */
#define PORT_DIGITAL_ENABLE_REG_OFFSET    (0x51C) /* Digital Enable Register Offset */
#define PORT_LOCK_REG_OFFSET              (0x520) /* Lock Register Offset */
#define PORT_COMMIT_REG_OFFSET            (0x524) /* Commit Register Offset */
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   (0x528) /* Analog Mode Selection Register Offset */
#define PORT_CTL_REG_OFFSET               (0x52C) /* Control Register Offset */
#define PORT_OPEN_DRAIN_REG_OFFSET        (0x50C) /* Open drain Register Offset */

#define SYSCTL_REGCGC2_REG                (*((volatile uint32 *)0x400FE108)) /* system control register to enable clock for the ports */

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

#endif /* PORT_REGS_H */
