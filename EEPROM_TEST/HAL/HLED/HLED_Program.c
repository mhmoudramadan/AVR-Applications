/*
 * HLED.Program.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Dell
 */

#include "../../LIB/LSTD_TYPES.h"
#include "../../MCAL/MDIO/MDIO_Interface.h"
#include "HLED_Interface.h"


/*******led initialize       ***********/

ErrorState HLED_Errorstate_Led_Init( LED_T* copy_LED_object)
{
	ErrorState Loc_ErrorState_Error_state=OK;
	Loc_ErrorState_Error_state = MDIO_Errorstate_SetPinDirection(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_OUTPUT);
		return Loc_ErrorState_Error_state;
}

/********* led on              ***********/
ErrorState HLED_Errorstate_Led_On(LED_T* copy_LED_object)
{
	ErrorState Loc_ErrorState_Error_state=OK;

	if(copy_LED_object->LedActiveState==ACTIVE_HIGH)
	{
		MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_HIGH);
	}
	else if(copy_LED_object->LedActiveState==ACTIVE_LOW)
	{
		MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_LOW);
	}
	else
	{
		Loc_ErrorState_Error_state=NOK;
	}

	return Loc_ErrorState_Error_state;
	}

/***                        leed off                  ****/
	ErrorState HLED_Errorstate_Led_Off(LED_T* copy_LED_object)
	{
		ErrorState Loc_ErrorState_Error_state=OK;

		if(copy_LED_object->LedActiveState==ACTIVE_HIGH)
		{
			MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_LOW);
		}
		else if(copy_LED_object->LedActiveState==ACTIVE_LOW)
		{
			MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_HIGH);
		}
		else
		{
			Loc_ErrorState_Error_state=NOK;
		}

		return Loc_ErrorState_Error_state;
		}

	ErrorState HLED_Errorstate_Led_Toggle(LED_T* copy_LED_object)
	{
		static uint8 flag=0; // imp
		ErrorState Loc_ErrorState_Error_state=OK;
		if(flag==0)
		{
			MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_HIGH);
			flag=1;
		}
		else if(flag==1)
		{

			MDIO_Errorstate_SetPinValue(copy_LED_object->LedPort,copy_LED_object->LedPin,PIN_LOW);
			flag=0;
		}
		else
		{
			/*do nothing*/
		}
		return Loc_ErrorState_Error_state;
	}
