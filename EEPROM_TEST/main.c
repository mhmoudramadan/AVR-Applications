/*
 * main.c
 *
 *  Created on: Mar 11, 2022
 *      Author: Dell
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MTWI/MI2C_Interface.h"
#include"HAL/HEEPROM/HEEPROM_Interface.h"
#include"HAL/HLED/HLED_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"
#define F_CPU 16000000UL
#include<util/delay.h>

LED_T led1={MDIO_PORTC,PIN7,ACTIVE_HIGH};
int main(void)
{
	/*LCD PIN initialize*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN4,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN5,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN6,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTA,PIN7,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RS_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,RW_PIN,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HCLCD_ControlPort,E_PIN,PIN_OUTPUT);
	/*LCD initialize*/
	HAL_VidHCLCD_4BitModeInit();
	HAL_VidHCLCD_4BitModeWriteString((uint8*)"welcomeEEPROM");
	_delay_ms(1000);

	uint8 Loc_uint8data;
//	uint8 Loc_uint8data1;
	HLED_Errorstate_Led_Init(&led1);
	MTWI_VidInitMaster(0);
	HEEPROM_VidSendDataByte(0,0,100);
	Loc_uint8data=HEEPROM_VidReadDataByte(0,0);
	//HEEPROM_VidSendDataByte(1,1,100);
	//Loc_uint8data1=HEEPROM_VidReadDataByte(1,1);
	while(1)
	{
		if(Loc_uint8data==10)
			{

			}
			else
			{
				HLED_Errorstate_Led_On(&led1);
				HAL_VidHCLCD_4BitModeWriteString(Loc_uint8data);
				/*Do Nothing*/
			}
	}
}
