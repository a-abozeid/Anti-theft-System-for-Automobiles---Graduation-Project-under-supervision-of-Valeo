 /******************************************************************************
 *
 * Module: Sw_Delay
 *
 * File Name: Sw_Delay.c
 *
 * Description: Source file for The Software Delay
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#include "Sw_Delay.h"


/*******************************************************************************
 * [Name]: Delay_ms
 * [Parameters]: uint64 time_ms
 * [Return]: void (none)
 * [Description]: The Function responsible for The Delay (mili) in the internal
 *                Operations of the peripherals and Hardware Components that don't 
 *                need accurate timing using Timers like (Systic or GPT).
 ********************************************************************************/
void Delay_ms(uint64 time_ms)
{
    volatile uint64 count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * time_ms) );
}


/*******************************************************************************
 * [Name]: Delay_us
 * [Parameters]: uint64 time_us
 * [Return]: void (none)
 * [Description]: The Function responsible for The Delay (micro) in the internal
 *                Operations of the peripherals and Hardware Components that don't 
 *                need accurate timing using Timers like (Systic or GPT).
 ********************************************************************************/
void Delay_us(uint64 time_us)
{
    volatile uint64 count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MICRO_SECOND * time_us) );
}

