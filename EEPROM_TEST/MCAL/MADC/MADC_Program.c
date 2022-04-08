/*
 * MADC_Program.c
 *
 *  Created on: Feb 5, 2022
 *      Author: Dell
 */
#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"MADC_Private.h"
#include"MADC_Interface.h"
#include"MADC_Config.h"

void (*MADC_CALLBACK)(void);

void MADC_VidSingleConversion_Init(void)
{
	/* 1-Select Reference Volt*/
#if MADC_SET_REFERENCVOLT == MADC_Vref_AVCC
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
#elif MADC_SET_REFERENCVOLT == MADC_Vref_INTERNAL_2_56
	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);
#else
#error"Reference Volt Option Is Not Valid.."
#endif
	/*  2-Select Left Or Right Adjustment Result*/
#if MADC_SET_ADJUSTRESULT==MADC_RIGHT_ADJUST
	SET_BIT(ADMUX,5);
#elif MADC_SET_ADJUSTRESULT ==MADC_LEFT_ADJUST
	CLR_BIT(ADMUX,5);
#else
	#error"Adjustment Result Is Not Valid.. "
#endif
	/*  3-Select ADC PreScaler*/
	ADCSRA&=0xF8;
	ADCSRA|=ADC_SET_PRESCALER;
	 /* 4-Enable ADC peripheral*/
	SET_BIT(ADCSRA,7);
}

void MADC_VidAutoTrigger_Init(void)
{
	/*1-Auto trigger Enable*/
	SET_BIT(ADCSRA,5);
	 /*2-ADC_Auto_Trigger_Source*/
#if MADC_SET_AUTO_TRIGGER_SOURCE ==MADC_FREERUNNING

	 SFIOR&=0x1F;
	SFIOR|=MADC_FREERUNNING;
#else
#error "Auto Trigger Source Is Not Valid.."
#endif
}

void MADC_VidInterrupt_Enable(void)
{
 /* 1-Set ADC Interrupt Enable */
	SET_BIT(ADCSRA,3);
}

void MADC_VidADCStartSingleConversion(uint8 copy_uint8Channel)
{
	/*1-Select Analog Channels
	 * single Ended or Differential */
#if MADC_SET_ANALOGCHANNEL ==  MADC_SINGLEENDED_CHANNEL
	ADMUX&=0xE0;
	ADMUX|=copy_uint8Channel;
#else
#error "Analog Channel Is Not Valid.."
#endif
	/* 2-Start Conversion*/
	SET_BIT(ADCSRA,6);
	/*wait until flag is set to 1*/
	while(GET_BIT(ADCSRA,4)==0);

}
void MADC_VidADCStartSingleConversion_With_Interrupt(uint8 copy_uint8Channel)
{
#if MADC_SET_ANALOGCHANNEL == MADC_SINGLEENDED_CHANNEL
	ADMUX&=0xE0;
	ADMUX|=copy_uint8Channel;
	SET_BIT(ADCSRA,6);
#else
	#error "Analog Channel Is Not Valid .."
#endif
}

uint16 MADC_uint16Read(void)
{
	uint16 ADC;
	/*1- right adjust*/
#if MADC_SET_ADJUSTRESULT==MADC_RIGHT_ADJUST

	ADC=ADCH;
	ADC|=ADCL<<8;
	return ADC;

	/*2-left adjust*/
/*#elif MADC_SET_ADJUSTRESULT==MADC_LEFT_ADJUST*/

 #else
	#error"Analog Channel Is Not Valid .."
#endif
	//return ADC;
}
void MADC_SetCallBack(void(*PtrToFun)(void))
{
	MADC_CALLBACK=PtrToFun;
}
void __vector_16(void)  __attribute__((signal));
void __vector_16(void)  	{
	MADC_CALLBACK();
}
