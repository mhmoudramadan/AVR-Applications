/*
 * MTIMER0_Program.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Dell
 */
#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#include"MTIMER0_Private.h"
#include"MTIMER0_Config.h"

void (*MTIMER0_CALLBACK)(void);
void MTIMER0_VidInit(void)
{
	/*1-Set Timer Mode*/
#if TIMER0_SETMODE == TIMER0_CTCMODE
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	#if TIMER0_CTCMODE_OC0PINMODE == TIMER0_CTCMODE_TOGGLE_OC0PIN
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
	#elif TIMER0_CTCMODE_OC0PINMODE==TIMER0_CTCMODE_SET_OC0PIN
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	#elif TIMER0_CTCMODE_OC0PINMODE==TIMER0_CTCMODE_CLR_OC0PIN
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	#elif TIMER0_CTCMODE_OC0PINMODE==TIMER0_CTCMODE_NOTCONNECTED_OC0PIN
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,4);
	#else #error "OC0 PIN Is Not Valid.."
	#endif
	/*CTC Enable interrupt */
	SET_BIT(TIMSK,1);
#elif TIMER0_SETMODE == TIMER0_NORMALMODE
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
	/*OVERFLOW  Enable interrupt */
	SET_BIT(TIMSK,0);

#elif TIMER0_SETMODE==TIMER0_FASTPWMMODE
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
  #if TIMER0_PWMMODE_OC0PINMODE==TIMER0_PWMMODE_NON_INVERTING
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
  #elif TIMER0_PWMMODE_OC0PINMODE==TIMER0_PWMMODE_INVERTING
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
 #else
	#error" OC0 PIN Is Not Valid.."
  #endif

#elif TIMER0_SETMODE==TIMER0_PHASECORRECTPWMMODE
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
  #if TIMER0_PWMMODE_OC0PINMODE==TIMER0_PWMMODE_NON_INVERTING
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
  #elif TIMER0_PWMMODE_OC0PINMODE==TIMER0_PWMMODE_INVERTING
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
  #else
	#error"OC0 PIN Is Not Valid.."
 #endif

#else
	#error"TIMER0 MODE Is Not Valid.."
#endif
	/*Set PreScaler*/
	TCCR0&=0xF8;
	TCCR0|=TIMER0_SETPRESCALER;
}
uint8 MTIMER0_uint32Read(void)
{
	return TCNT0;
}
void MTIMER0_VidSetPreLoad(uint8 copy_uint8PreLoad)
{
	TCNT0=copy_uint8PreLoad;
}
void MTIMER0_VidSetCTCRegister(uint8 copy_uint8CTCValue)
{
	OCR0=copy_uint8CTCValue;
}
void MTIMER0_VidTimerOverFlow_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER0_CALLBACK=PtrToFun;
}
void MTIMER0_VidTimerCTC_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER0_CALLBACK=PtrToFun;
}

/*CTC*/
void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	MTIMER0_CALLBACK();
}
/*OVERFLOW*/
void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	MTIMER0_CALLBACK();
}
