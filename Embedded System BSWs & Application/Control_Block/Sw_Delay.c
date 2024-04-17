 /******************************************************************************
 *
 * Module: Sw_Delay
 *
 * File Name: Sw_Delay.c
 *
 * Description: Source file for Sw_Delay
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "sw_delay.h"

/*******************************************************************************************************
 * [Name]: Delay_ms
 * [Parameters]: uint64 n
 * [Return]: void (none)
 * [Description]: The Function responsible for The Delay in the internal Operations of the peripherals
 * and Hardware Components that don't need accurate timing using Timers like (Systic or GPT).
 ********************************************************************************************************/
void Delay_ms(unsigned long long timeInMs)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * timeInMs) );
}
