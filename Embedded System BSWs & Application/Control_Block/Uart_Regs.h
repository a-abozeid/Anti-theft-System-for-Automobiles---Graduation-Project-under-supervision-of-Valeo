/* HEADER */
#ifndef UART_REGS_H
#define UART_REGS_H


#define UART0_BASE_ADDRESS           (0x4000C000)
#define UART1_BASE_ADDRESS           (0x4000D000)
#define UART2_BASE_ADDRESS           (0x4000E000)
#define UART3_BASE_ADDRESS           (0x4000F000)
#define UART4_BASE_ADDRESS           (0x40010000)
#define UART5_BASE_ADDRESS           (0x40011000)
#define UART6_BASE_ADDRESS           (0x40012000)
#define UART7_BASE_ADDRESS           (0x40013000)


#define UART_CTL_REG_OFFSET          (0x030) /* UART Control */
#define UART_IBRD_REG_OFFSET         (0x024) /* UART Integer Baud-Rate Divisor */
#define UART_FBRD_REG_OFFSET         (0x028) /* UART Fractional Baud-Rate Divisor */
#define UART_CC_REG_OFFSET           (0xFC8) /* UART Clock Configuration */
#define UART_LCRH_REG_OFFSET         (0x02C) /* UART Line Control */
#define UART_F_REG_OFFSET            (0x018) /* UART Flag */
#define UART_D_REG_OFFSET            (0x000) /* UART Data */
#define UART_IM_REG_OFFSET           (0x038) /* UART Interrupt Mask */
#define UART_IC_REG_OFFSET           (0x044) /* UART Interrupt Clear */
/* Uart Run Mode Clock Gating Control Register to enable clock for the Uart modules */
#define UART_RCGC_REG  (*((volatile uint32 *)0x400FE618))


#define UART_EN_BIT                     (0u) 
#define UART_PARITY_EN_BIT              (1U)
#define UART_EVEN_PARITY_SELECT_BIT     (2U)
#define UART_TWO_STOP_BITS_SELECT_BIT   (2U)
#define UART_RXIM_BIT                   (4U)
#define UART_TXIM_BIT                   (5U)
#define UART_RXIC_BIT                   (4U)
#define UART_TXIC_BIT                   (5U)
#endif
