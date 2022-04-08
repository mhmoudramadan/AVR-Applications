/*
 * HEPPROM_Program.c
 *
 *  Created on: Mar 11, 2022
 *      Author: Dell
 */

#ifndef HAL_HEPPROM_HEPPROM_PROGRAM_C_
#define HAL_HEPPROM_HEPPROM_PROGRAM_C_

#include"../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MTWI/MI2C_Interface.h"
#include<util/delay.h>

#include "HEEPROM_Private.h"

void HEEPROM_VidSendDataByte(uint8 copy_uint8PageNumber,uint8 copy_uint8LocationAddress, uint8 copy_uint8Data)
{
	/*Handle EEPROM Address*/
	uint8 Loc_uint8SlaveAddress;
	Loc_uint8SlaveAddress=EEPROM_FIXEDADDRESS|(copy_uint8PageNumber);
	/*send Start Condition*/
	MTWI_SendSatrtCondition();
	/*Send SlA(EEPROM Add +Page number) with write*/
	MTWI_SendSalveAddressWithWrite(Loc_uint8SlaveAddress);
	/*Send Location Addressed*/
	MTWI_MasterWriteDataByte(copy_uint8LocationAddress);
	/*Send Data*/
	MTWI_MasterWriteDataByte(copy_uint8Data);
	/*Stop Condition*/
	MTWI_SendStopCondtion();
	/*Data Sheet*/
	_delay_ms(10);
}

uint8 HEEPROM_VidReadDataByte(uint8 copy_uint8PageNumber,uint8 copy_uint8LocationAddress)
{
	uint8 Loc_uint8Data;
	/*Handle EEPROM Address*/
	uint8 Loc_uint8SlaveAddress;
	Loc_uint8SlaveAddress=EEPROM_FIXEDADDRESS|(copy_uint8PageNumber);
	/*send Start Condition*/
	MTWI_SendSatrtCondition();
	/*Send SlA(EEPROM Add +Page number) with write*/
	MTWI_SendSalveAddressWithWrite(Loc_uint8SlaveAddress);
	/*Send Location Address*/
	MTWI_MasterWriteDataByte(copy_uint8LocationAddress);
	/*Send Repeated Start*/
	MTWI_SendSatrtRepeatedCondition();
	/*Send SlA(EEPROM Add +Page number) with write*/
	MTWI_SendSalveAddressWithRead(Loc_uint8SlaveAddress);
	/*Read Data*/
	MTWI_MasterReadDataByte(&Loc_uint8Data);
	/*Stop Condition*/
	MTWI_SendStopCondtion();
	return Loc_uint8Data;
}

#endif /* HAL_HEPPROM_HEPPROM_PROGRAM_C_ */
