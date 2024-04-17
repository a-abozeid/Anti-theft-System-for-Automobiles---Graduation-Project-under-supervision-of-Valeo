 /******************************************************************************
 *
 * Module: Sw_Delay
 *
 * File Name: Sw_Delay.h
 *
 * Description: Header file for The Software Delay
 *
 * Author: Youssef El-Nemaky
 ******************************************************************************/

#ifndef SW_DELAY_H
#define SW_DLEAY_H


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/

#include"Std_Types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

#define NUMBER_OF_ITERATIONS_PER_ONE_MICRO_SECOND 0.762



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*******************************************************************************
 * [Name]: Delay_ms
 * [Parameters]: uint64 time_ms
 * [Return]: void (none)
 * [Description]: The Function responsible for The Delay (mili) in the internal
 *                Operations of the peripherals and Hardware Components that don't 
 *                need accurate timing using Timers like (Systic or GPT).
 ********************************************************************************/
void Delay_ms(uint64 time_ms);


/*******************************************************************************
 * [Name]: Delay_us
 * [Parameters]: uint64 time_us
 * [Return]: void (none)
 * [Description]: The Function responsible for The Delay (micro) in the internal
 *                Operations of the peripherals and Hardware Components that don't 
 *                need accurate timing using Timers like (Systic or GPT).
 ********************************************************************************/
void Delay_us(uint64 time_us);


#endif /* SW_DELAY_H*/