/*
 * main.c
 *
 *  Created on: Feb 26, 2022
 *      Author: Dell
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"MCAL/MUART/MUART_Interface.h"
#include"HAL/HCLCD/HCLCD_Config.h"
#include"HAL/HCLCD/HCLCD_Interface.h"

#define F_CPU 16000000UL
#include<util/delay.h>

int main (void)
{
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
	/*SET Rx  D0 And Tx D1 Pins*/
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN0,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(MDIO_PORTD,PIN1,PIN_OUTPUT);
	/*UART Initialize*/
	MUART_VidInit();
	uint8 Loc_uint8Char;
	while(1)
	{
		Loc_uint8Char=MUART_uint8ReciverChar();
		HAL_VidHCLCD_4BitModeWriteChar(Loc_uint8Char);
	}
	return 0;
}
