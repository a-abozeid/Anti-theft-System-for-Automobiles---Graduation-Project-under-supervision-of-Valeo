 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.c
 *
 * Description: Source File for GPT 
 *
 * Created on: June 11, 2022
 *
 * Authors: Hazem Yousery
 *
 *******************************************************************************/
#include "GPT.h"

static volatile void (*Timer1_CallBackPtr)(void) = NULL_PTR;
static volatile void (*Timer0_CallBackPtr)(void) = NULL_PTR;
static volatile unsigned char timer1Counter = 0;
static volatile unsigned char timer0Counter = 0;


void Timer1_Init()
{

    volatile unsigned long delay = 0;
    RCGCTIMER |= (1<<1);
    delay = RCGCTIMER;
   
    GPTMCTL_T1 = 0;

    GPTMCFG_T1=0x00; /* 32 bit timer configuration */

	GPTMTAMR_T1 = 0x02; /* Periodic mode - count down */

    GPTMTAILR_T1 = 960000000 - 1; /* A timer match value of 1 minute */

    GPTMIMR_T1|=(1<<0); /* GPTM Timer A Time Out Event Interrupt Mask (Interrupt is enabled in this mode) */

    GPTMICR_T1 |= (1<<0); /* Clear interrupt flag */

    GPTMCTL_T1 |= (1<<0); /* GPTM Timer A Enable to start the timer*/

}

void Timer1_Start()
{
	GPTMCTL_T1|=(1<<0); /* GPTM Timer A Enable to start the timer*/

}


void Timer1_Stop()
{
	GPTMCTL_T1&=(~(1<<0)); /* GPTM Timer A Disable to stop the timer */
}

void Timer1_Handler()
{       
    timer1Counter++; /* Increment the counter value */
    if(timer1Counter == 5){ /* Check if 5 minutes have passed */
        if (Timer1_CallBackPtr == NULL_PTR)
        {
            /*do nothing*/
        }
        else
        {
            (*Timer1_CallBackPtr)(); /* Call back the function */
        }
        timer1Counter = 0;
    }
    GPTMICR_T1 |= (1<<0); /* Clear the interrupt flag bit */
        
}

void Timer1_setCallBack(void (*ptr)())
{
   Timer1_CallBackPtr = ptr; /* Set the call back function ptr */
}

uint32 Timer1_ReadValue(){
    return GPTMTAR_T1;
}


void Timer0_Init()
{

    volatile unsigned long delay = 0;
    RCGCTIMER |= (1<<0);
    delay = RCGCTIMER;
   
    GPTMCTL_T0 = 0;

    GPTMCFG_T0=0x00; /* 32 bit timer configuration */

	GPTMTAMR_T0 = 0x02; /* Periodic mode - count down */

    GPTMTAILR_T0 = 160000000 - 1; /* A timer match value of 1 minute */

    GPTMIMR_T0|=(1<<0); /* GPTM Timer A Time Out Event Interrupt Mask (Interrupt is enabled in this mode) */

    GPTMICR_T0 |= (1<<0); /* Clear interrupt flag */

    GPTMCTL_T0 |= (1<<0); /* GPTM Timer A Enable to start the timer*/

}

void Timer0_Start()
{
	GPTMCTL_T0|=(1<<0); /* GPTM Timer A Enable to start the timer*/

}


void Timer0_Stop()
{
	GPTMCTL_T0&=(~(1<<0)); /* GPTM Timer A Disable to stop the timer */
}

void Timer0_Handler()
{       
    timer0Counter++; /* Increment the counter value */
    if(timer0Counter == 1){ /* Check if 5 minutes have passed */
        if (Timer0_CallBackPtr == NULL_PTR)
        {
            /*do nothing*/
        }
        else
        {
            (*Timer0_CallBackPtr)(); /* Call back the function */
        }
        timer0Counter = 0;
    }
    GPTMICR_T0 |= (1<<0); /* Clear the interrupt flag bit */
        
}

void Timer0_setCallBack(void (*ptr)())
{
   Timer0_CallBackPtr = ptr; /* Set the call back function ptr */
}
