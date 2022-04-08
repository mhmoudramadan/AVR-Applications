/*
 * MTIMER0_Private.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTIMER0_MTIMER0_PRIVATE_H_
#define MCAL_MTIMER0_MTIMER0_PRIVATE_H_

#define TCCR0  *((volatile uint8*)0x53)
#define TIMSK  *((volatile uint8*)0x59)
#define TCNT0  *((volatile uint8*)0x52)
#define OCR0   *((volatile uint8*)0x5C)

#define TIMER0_CTCMODE               0
#define TIMER0_NORMALMODE            1
#define TIMER0_FASTPWMMODE           2
#define TIMER0_PHASECORRECTPWMMODE   3

#define TIMER0_CTCMODE_TOGGLE_OC0PIN        0
#define TIMER0_CTCMODE_SET_OC0PIN           1
#define TIMER0_CTCMODE_CLR_OC0PIN           2
#define TIMER0_CTCMODE_NOTCONNECTED_OC0PIN  3

#define TIMER0_PWMMODE_NON_INVERTING  0
#define TIMER0_PWMMODE_INVERTING      1

#define TIMER0_NOPRESCALER                 1
#define TIMER0_PRESCALER_8                 2
#define TIMER0_PRESCALER_64                3
#define TIMER0_PRESCALER_256               4
#define TIMER0_PRESCALER_1024              5
#define TIMER0_EXTRERNALCLOCK_FALLINGEDGE  6
#define TIMER0_EXTRERNALCLOCK_RISINGEDGE   7

#endif /* MCAL_MTIMER0_MTIMER0_PRIVATE_H_ */
