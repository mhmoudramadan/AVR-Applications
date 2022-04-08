/*
 * HSTTEPEER_Program.c
 *
 *  Created on: Jan 29, 2022
 *      Author: Dell
 */

#include "../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include "../HSTEPPER/HStepper_Config.h"
#include "../HSTEPPER/HStepper_Interface.h"
#define F_CPU 16000000UL
#include<util/delay.h>
void HStepper_Init(void)
{
	MDIO_Errorstate_SetPinDirection(STEPPER_PORT,STEPPER_COIL1,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(STEPPER_PORT,STEPPER_COIL2,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(STEPPER_PORT,STEPPER_COIL3,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(STEPPER_PORT,STEPPER_COIL4,PIN_OUTPUT);
}
void HStepper_SetStepsDirection(uint16 copy_uint16Steps,uint8 copy_uint8Direction)
{
	switch(copy_uint8Direction)
		{
	                         /*clock wise */
		     case CW:
			for(uint16 i=0 ;i<copy_uint16Steps;i++)
					{
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_LOW);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
					_delay_ms(MAX_SPEED_DELAY);

					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_LOW);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
					_delay_ms(MAX_SPEED_DELAY);

					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_LOW);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
					_delay_ms(MAX_SPEED_DELAY);

					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
					MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_LOW);
					_delay_ms(MAX_SPEED_DELAY);
					}
			break;

                                        /* counter clock wise*/
		case CCW :
			for(uint16 i=0 ;i<copy_uint16Steps;i++)
			{
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_LOW);
				_delay_ms(MAX_SPEED_DELAY);

				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_LOW);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
				_delay_ms(MAX_SPEED_DELAY);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_LOW);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
				_delay_ms(MAX_SPEED_DELAY);

				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL1,PIN_LOW);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL2,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL3,PIN_HIGH);
				MDIO_Errorstate_SetPinValue(STEPPER_PORT,STEPPER_COIL4,PIN_HIGH);
				_delay_ms(MAX_SPEED_DELAY);
				}
			break;
		}
}
