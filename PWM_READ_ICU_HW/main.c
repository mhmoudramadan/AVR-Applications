/*
 * main.c
 *
 *  Created on: Feb 23, 2022
 *      Author: Dell
 */

#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MTIMER2/MTIMER2_Config.h"
#include"MCAL/MTIMER2/MTIMER2_Interface.h"
#include"MCAL/MTIMER1/MTIMER1_Config.h"
#include"MCAL/MTIMER1/MTIMER1_Interface.h"
#include"MCAL/MGIE/MGIE_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"
#include"HAL/HLED/HLED_Interface.h"
#define F_CPU 16000000UL
#include<util/delay.h>

            /*Initialize Led */
LED_T led0={MDIO_PORTC,PIN2,ACTIVE_HIGH};
LED_T led1={MDIO_PORTC,PIN7,ACTIVE_HIGH};
LED_T led2={MDIO_PORTD,PIN3,ACTIVE_HIGH};
         /*Timer 1 Over Flow */
uint32 counts=0;
void APP_TOV(void)
{
	counts++;
}
        /*ICU Interrupt Code*/
uint32 t1;
uint32 t2;
uint32 t3;
uint8 Endflag=0;
void APP_TO_ICU(void)
{
	static uint8 flag=0;
	if (flag==0)
	{
		t1=MTIMER1_uint32Read_ICR1()+(counts*65536);
		MTIMER1_VidICU_SelectEdge(ICU_FALLING_EDGE);
		HLED_Errorstate_Led_On(&led0);
		flag=1;
	}
	else if(flag==1)
	{
		t2=MTIMER1_uint32Read_ICR1()+(counts*65536);
		MTIMER1_VidICU_SelectEdge(ICU_RISING_EDGE);
		HLED_Errorstate_Led_On(&led1);
		flag=2;
	}
	else if(flag==2)
	{
		t3=MTIMER1_uint32Read_ICR1()+(counts*65536);
		flag=0;
		counts=0;
		Endflag=1;

	}
}

int main()
{
	uint32 freq;
	uint8 DutyCylce;
	                      /*Initialize LCD PINS*/
	                        /*Control Pins*/
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	                        /*data Pins*/
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN7,PIN_OUTPUT);
	                     /*Welcome Message*/
	HAL_VidHCLCD_4BitModeInit();
	HAL_VidHCLCD_4BitModeWriteString("welcome..");
	_delay_ms(1000);
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString("freq=");
	HAL_VidHCLCD_4BitModeSetPosition(2,0);
	HAL_VidHCLCD_4BitModeWriteString("DutyCylce=");
	HAL_VidHCLCD_4BitModeSetPosition(1,12);
	HAL_VidHCLCD_4BitModeWriteString("HZ");
	HAL_VidHCLCD_4BitModeSetPosition(2,15);
	HAL_VidHCLCD_4BitModeWriteString("%");
	                     /*Initialize LED**/
	HLED_Errorstate_Led_Init(&led0);
	HLED_Errorstate_Led_Init(&led1);
	HLED_Errorstate_Led_Init(&led2);

	           /*OC2 PIN AS OUTPUT*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN7,PIN_OUTPUT);
	          /*SET ICU PIN As Input*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN6,PIN_INPUT);

	            /*Generate Timer 2 Fast PWM Mode --> Non Inverting Pin -->PreScaler 128*/
	MTIMER2_VidInit();
	MTIMER2_VidSetCTCRegister(100); //Duty Cycle
	            /*Initialize Timer 1"normal mode prescaler 64 " */
	MTIMER1_VidTimer1_OverFlow_SetCallBack(APP_TOV);
	MTIMER1_VidTimer1_ICU_SetCallBack(APP_TO_ICU);
	MTIMER1_VidInit();
	         /*Initialize ICU --> rising Edge*/
	MTIMER1_VidICU_SelectEdge(ICU_RISING_EDGE);
	MTIMER1_VidInit_ICU();
	            /*Enable Global Interrupt*/
	MGIE_Enable();
	while(1)
	{
		/*T (on)=T2-T1
		 * t (off)=T3-T2
		 * T (period)=T3-T1
		 * freq=(F_CPU/((T period * tick time )*/
		if(Endflag==1)
		{
			DutyCylce=((t2-t1)*100)/(t3-t1);
			freq=(1000000)/((t3-t1)*4); 
			HAL_VidHCLCD_4BitModeSetPosition(1,6);
			HAL_VidHCLCD_4BitModeWriteNumber(freq);
			HAL_VidHCLCD_4BitModeSetPosition(2,10);
			HAL_VidHCLCD_4BitModeWriteNumber(DutyCylce);
			HLED_Errorstate_Led_On(&led2);
			// Logical Code
		}
	}
	return 0;
}
