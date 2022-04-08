/*
 * main.c
 *
 *  Created on: Feb 22, 2022
 *      Author: Dell
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MTIMER0/MTIMER0_Config.h"
#include"MCAL/MTIMER0/MTIMER0_Interface.h"
#include"MCAL/MTIMER1/MTIMER1_Config.h"
#include"MCAL/MTIMER1/MTIMER1_Interface.h"
#include"MCAL/MEXTI/MEXTI_Config.h"
#include"MCAL/MEXTI/MEXTI_Interface.h"
#include"MCAL/MGIE/MGIE_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HLED/HLED_Interface.h"
#define F_CPU 16000000UL
#include"util/delay.h"

/*Over Flow Counts*/
uint32 count=0;
void APP_TOV(void)
{
	count++;
}
/*Led To Check */
LED_T led1={MDIO_PORTC,PIN2,ACTIVE_HIGH};
LED_T led0={MDIO_PORTC,PIN7,ACTIVE_HIGH};
/*ISR */
uint8 Endfalg=0;
uint32 t1;
uint32 t2;
uint32 t3;
void APP_TOV_EXT1(void)
{
	static uint8 flag=0;
	if(flag==0)
	{
		t1=MTIMER0_uint32Read()+count;
		MEXTI_VidSenseControlSelect(EXTI1,MEXTI_FALLING_EDGE);
		flag=1;
		HLED_Errorstate_Led_On(&led1);
	}
	else if(flag==1)
	{
		t2=MTIMER0_uint32Read()+count;
		MEXTI_VidSenseControlSelect(EXTI1,MEXTI_RISING_EDGE);
		flag=2;

	}
	else if(flag==2)
	{
		t3=MTIMER0_uint32Read()+count;
		Endfalg=1;
		//flag=0;
		count=0;
	}

}
int main()
{
	uint32 first;
	uint32 second;
	/*Initialize LED*/
	HLED_Errorstate_Led_Init(&led0);
	HLED_Errorstate_Led_Init(&led1);
	/* Set buzzer to ALarm */
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN3,PIN_OUTPUT);
	/*Set Pin Of OC PINS*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN3,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN5,PIN_OUTPUT);
	/*Initialize LCD */
	/*Control Pin*/
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	/*Data Pin*/
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_DataPort,PIN7,PIN_OUTPUT);

	/*Initialize LCD and Welcome message*/
	HAL_VidHCLCD_4BitModeInit();
	HAL_VidHCLCD_4BitModeWriteString("welcome..");
	_delay_ms(1000);
	HAL_VidHCLCD_4BitModeSendCommand(0x01);
	HAL_VidHCLCD_4BitModeSetPosition(1,0);
	HAL_VidHCLCD_4BitModeWriteString("t1=");
	HAL_VidHCLCD_4BitModeSetPosition(2,0);
	HAL_VidHCLCD_4BitModeWriteString("t2=");

	/*Generate  FASt PWM Form Timer 1*/
	MTIMER1_VidInit();
	MTIMER1_VidSetCTCRegister_CHA(1000);
	MTIMER1_VidSetCTCRegister_ICR1(2000);

	/*Timer 0 Normal Mode*/
	MTIMER0_VidTimerOverFlow_SetCallBack(APP_TOV);
	MTIMER0_VidInit();

	/*External Interrupt 1*/
	MEXTI1_VidSetCallBack(APP_TOV_EXT1);
	MEXTI_VidInitEXTI1();
	MGIE_Enable();
	while(1)
	{

		if(Endfalg==1)
		{
			first=t2/(t3-t1);
			second=(t2-t1);
			HAL_VidHCLCD_4BitModeSetPosition(1,4);
			HAL_VidHCLCD_4BitModeWriteNumber(first);
			HAL_VidHCLCD_4BitModeSetPosition(2,4);
			HAL_VidHCLCD_4BitModeWriteNumber(second);
			HLED_Errorstate_Led_Toggle(&led0);
			//HLED_Errorstate_Led_Off(&led1);
			MDIO_Errorstate_SetPinValue(MDIO_PORTA,PIN3,PIN_HIGH);
			_delay_ms(1000);
			MDIO_Errorstate_SetPinValue(MDIO_PORTA,PIN3,PIN_LOW);
			_delay_ms(1000);
			Endfalg=0;
		}
		if(Endfalg==2)
		{
			//MDIO_Errorstate_SetPinValue(MDIO_PORTA,PIN3,PIN_HIGH);
		}


	}
	return 0;
}


