/*
 * MTIMER2_Program.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Dell
 */
#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"MTIMER2_Private.h"
#include"MTIMER2_Config.h"


void (*MTIMER2_CALLBACK)(void);
void MTIMER2_VidInit(void)
{
	/*Timer2 Modes Option*/
	/*1-CTC Mode */
#if TIMER2SETMODE == TIMER2_CTCMODE
	SET_BIT(TCCR2,3);
	CLR_BIT(TCCR2,6);
	/*CTC Interrupt Enable */
	SET_BIT(TIMSK,7);
	/*OC2 PIN Options*/
	#if TIMER2_CTCMODE_OC2PINMODE == TIMER2_CTCMODE_TOGGLE_OC2PIN
	 SET_BIT(TCCR2,4);
	 CLR_BIT(TCCR2,5);
	#elif TIMER2_CTCMODE_OC2PINMODE == TIMER2_CTCMODE_SET_OC2PIN
	 SET_BIT(TCCR2,4);
	 SET_BIT(TCCR2,5);
	#elif TIMER2_CTCMODE_OC2PINMODE == TIMER2_CTCMODE_CLR_OC2PIN
	 CLR_BIT(TCCR2,4);
	 SET_BIT(TCCR2,5);
	#elif TIMER2_CTCMODE_OC2PINMODE == TIMER2_CTCMODE_NOTCONNECTED_OC2PIN
	 CLR_BIT(TCCR2,4);
	 CLR_BIT(TCCR2,5);
	#else
	 #error"Timer2 OC2 PIN Option Is Not Valid.."
	#endif
#elif TIMER2SETMODE == TIMER2_NORMALMODE
	CLR_BIT(TCCR2,3);
	CLR_BIT(TCCR2,6);
	/*OverFlow Interrupt Enable */
	SET_BIT(TIMSK,6);

#elif TIMER2SETMODE == TIMER2_FASTPWMMODE
	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,3);
  #if TIMER2_PWMMODE_OC2PINMODE==TIMER2_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
 #elif TIMER2_PWMMODE_OC2PINMODE==TIMER2_PWMMODE_INVERTING
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
 #else
	#error "PWM PIN IS NOT Valid.."
 #endif
#elif TIMER2SETMODE==TIMER2_PWMPHASECORRECTMODE
	SET_BIT(TCCR2,6);
	CLR_BIT(TCCR2,3);
  #if TIMER2_PWMMODE_OC2PINMODE==TIMER2_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
  #elif TIMER2_PWMMODE_OC2PINMODE==TIMER2_PWMMODE_INVERTING
	SET_BIT(TCCR2,4);
	SET_BIT(TCCR2,5);
  #else
   #error "OC2 PIN Option Is Not Valid.."
 #endif

#else
	#error"Timer2 Mode Options Is Not Valid.."
#endif

	              /*SET PRESCALER*/
	TCCR2&=0xF8;
	TCCR2|=MTIMER2_SET_PRESCALER;
}
void MTIMER2_VidSetPreLoad(uint8 copy_uint8PreLoadValue)
{
	TCNT2=copy_uint8PreLoadValue;
}
void MTIMER2_VidSetCTCRegister(uint8 copy_uint8CTCRegisteValue)
{
	OCR2=copy_uint8CTCRegisteValue;
}
void MTIMER2_VidTIMER2_OVERFLOW_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER2_CALLBACK=PtrToFun;
}
void MTIMER2_VidTIMER2_CTC_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER2_CALLBACK=PtrToFun;
}
           /*CTC*/
void __vector_4(void)   __attribute__((signal));
void __vector_4(void)
{
	MTIMER2_CALLBACK();
}
         /*overflow */
void __vector_5(void)   __attribute__((signal));
void __vector_5(void)
{
	MTIMER2_CALLBACK();
}
