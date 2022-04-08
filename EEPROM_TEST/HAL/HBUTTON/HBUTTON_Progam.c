/*
 * HBUTTON_Progam.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Dell
 */
#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"HBUTTON_Interface.h"

ErrorState  HBUTTON_Errorstate_Button_Init(Button_t* copy_Button_object)
{
	ErrorState Loc_ErrorState_Error_state=OK;
		Loc_ErrorState_Error_state = MDIO_Errorstate_SetPinDirection(copy_Button_object->ButtonPort,copy_Button_object->ButtonPin,PIN_INPUT);
			return Loc_ErrorState_Error_state;
}
ErrorState  HBUTTON_Errorstate_Button_Pressed(Button_t* copy_Button_object)
{

	uint8 Loc_Button_State;
	ErrorState Loc_ErrorState_Error_state=OK;
	if((copy_Button_object->ButtonActiveState)==PULL_DOWN)/*check 3la button activate state*/
	{
		/*pull down */
		MDIO_Errorstate_SetPinDirection(copy_Button_object->ButtonPort,copy_Button_object->ButtonPin,PIN_INPUT);
		MDIO_Errorstate_GetPinValue(copy_Button_object->ButtonPort,copy_Button_object->ButtonPin,&Loc_Button_State);
	}
	else if((copy_Button_object->ButtonActiveState)==PULL_UP)
	{
		MDIO_Errorstate_SetPinDirection(copy_Button_object->ButtonPort,copy_Button_object->ButtonPin,PIN_INPUT);
		/*internal pull up activate*/
		MDIO_Errorstate_GetPinValue(copy_Button_object->ButtonPort,copy_Button_object->ButtonPin,&Loc_Button_State);
	}
	else
	{
		Loc_ErrorState_Error_state=NOK;
	}

return Loc_ErrorState_Error_state;
}

