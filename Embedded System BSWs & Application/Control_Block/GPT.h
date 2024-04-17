 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: GPT.h
 *
 * Description: Header File for GPT 
 *
 * Created on: June 11, 2022
 *
 * Authors: Hazem Yousery
 *
 *******************************************************************************/
#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"
/* Timer 1 Registers */
#define GPTMTAPR_T1   (*((volatile unsigned long *)0x40031038))
#define GPTMCTL_T1 (*((volatile unsigned long*)0x4003100C))
#define GPTMCFG_T1 (*((volatile unsigned long*)0x40031000))
#define GPTMTAR_T1 (*((volatile unsigned long*)0x40031048))
#define GPTMTAMR_T1 (*((volatile unsigned long*)0x40031004))
#define GPTMTAILR_T1 (*((volatile unsigned long*)0x40031028))
#define GPTMRIS_T1 (*((volatile unsigned long*)0x4003101C))
#define GPTMICR_T1 (*((volatile unsigned long*)0x40031024))
#define GPTMIMR_T1 (*((volatile unsigned long*)0x40031018))
#define GPTMMIS_T1 (*((volatile unsigned long*)0x40031020))
#define RCGCTIMER (*((volatile unsigned long*)0x400FE604))

/* Timer 0 Registers */
#define GPTMTAPR_T0   (*((volatile unsigned long *)0x40030038))
#define GPTMCTL_T0 (*((volatile unsigned long *)0x4003000C))
#define GPTMCFG_T0 (*((volatile unsigned long *)0x40030000))
#define GPTMTAR_T0 (*((volatile unsigned long*)0x40030048))
#define GPTMTAMR_T0 (*((volatile unsigned long *)0x40030004))
#define GPTMTAILR_T0 (*((volatile unsigned long*)0x40030028))
#define GPTMRIS_T0 (*((volatile unsigned long*)0x4003001C))
#define GPTMICR_T0 (*((volatile unsigned long*)0x40030024))
#define GPTMIMR_T0 (*((volatile unsigned long *)0x40030018))
#define GPTMMIS_T0 (*((volatile unsigned long *)0x40030020))


void Timer1_Init();
void Timer1_Start();
void Timer1_Handler();
void Timer1_setCallBack(void (*ptr)());
void Timer1_Stop();
uint32 Timer1_ReadValue();
void Timer0_Init();
void Timer0_Start();
void Timer0_Handler();
void Timer0_setCallBack(void (*ptr)());
void Timer0_Stop();
uint32 Timer0_ReadValue();
#endif /* TIMER_H_ */
