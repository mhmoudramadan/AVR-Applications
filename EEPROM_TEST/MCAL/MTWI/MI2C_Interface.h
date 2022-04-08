/*
 * MI2C_Interface.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTWI_MI2C_INTERFACE_H_
#define MCAL_MTWI_MI2C_INTERFACE_H_

typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartConditionError,
	SlaveAddressWriteError,
	SlaveAddressReadError,
	MasterWriteByteError,
	MasterReadByteError,
}TWI_ErrorState;
/*TWI Init as a master*/
void MTWI_VidInitMaster(uint8 copy_uint8Address);
/*TWI Init as a Salve*/
void MTWI_VidInitSalve(uint8 copy_uint8Address);
/*TWI Start condition*/
TWI_ErrorState MTWI_SendSatrtCondition(void);
/*TWI Start Repeated Function*/
TWI_ErrorState  MTWI_SendSatrtRepeatedCondition(void);
/*TWI send  SLave Address with Write*/
TWI_ErrorState MTWI_SendSalveAddressWithWrite(uint8 copy_uint8SalveAddress);
/*TWI send SLave Address with Read*/
TWI_ErrorState MTWI_SendSalveAddressWithRead(uint8 copy_uint8SalveAddress);
/*TWI send data as a master*/
TWI_ErrorState MTWI_MasterWriteDataByte(uint8 copy_uint8Data);
/*TWI read data as a master*/
TWI_ErrorState MTWI_MasterReadDataByte(uint8 *copy_uint8Data);
/*TWI Stop condition*/
void MTWI_SendStopCondtion(void);
#endif /* MCAL_MTWI_MI2C_INTERFACE_H_ */
