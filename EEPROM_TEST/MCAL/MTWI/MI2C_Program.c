/*
 * MI2C_Program.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Dell
 */

#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include "../MTWI/MI2C_Config.h"
#include "../MTWI/MI2C_Interface.h"
#include "../MTWI/MI2C_Private.h"

/*TWI Init as a master*/

void MTWI_VidInitMaster(uint8 copy_uint8Address)
{
	/*Enable Ack*/
	SET_BIT(TWCR,6);
	/*Set SCL Freq to 400KHZ ,With 16MHZ system Freq--> "Rate Bit" */
	TWBR=3;
	/*Set PreScaler =1 */
	CLR_BIT(TWSR,1);
	CLR_BIT(TWSR,0);
	/*Enable TWI*/
	SET_BIT(TWCR,2);
	/*write Address */
	if(copy_uint8Address !=0)
	{
		TWAR=copy_uint8Address<<1; //3ashn homa 7 bit bs
	}
	else
	{
		//Nothing
	}
}

/*TWI Init as a Salve*/

void MTWI_VidInitSalve(uint8 copy_uint8Address)
{
	/*Enable Ack*/
	SET_BIT(TWCR,6);
		/*Enable TWI*/
	SET_BIT(TWCR,2);
	/*write Address */
	if(copy_uint8Address !=0)
	{
		TWAR=copy_uint8Address<<1; //3ashn homa 7 bit bs
	}
	else
	{
		//Nothing
	}
}

/*TWI Start condition*/
TWI_ErrorState MTWI_SendSatrtCondition(void)
{
	TWI_ErrorState Loc_Error=NoError;
	/*send satrt condition*/
	SET_BIT(TWCR,5);
	/*Clear  TWI flag*/
	SET_BIT(TWCR,7);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x08)
	{
		Loc_Error=StartConditionError;
	}
	else
	{
		/*Do nothing*/
	}
	return Loc_Error;
}
/*TWI Start Repeated Function*/
TWI_ErrorState  MTWI_SendSatrtRepeatedCondition(void)
{
	TWI_ErrorState Loc_Error=NoError;
		/*send satrt condition*/
		SET_BIT(TWCR,5);
		/*Clear  TWI flag*/
		SET_BIT(TWCR,7);
		/*wait until the operation finish and Flag Is Rasised*/
		while(GET_BIT(TWCR,7)==0);
		/*Check the operation statues*/
		if((TWSR&0xF8) != 0x10)
		{
			Loc_Error=RepeatedStartConditionError;
		}
		else
		{
			/*Do nothing*/
		}
		return Loc_Error;
}
/*TWI send  SLave Address with Write*/
TWI_ErrorState MTWI_SendSalveAddressWithWrite(uint8 copy_uint8SalveAddress)
{
	TWI_ErrorState Loc_Error=NoError;
	/*Send Salve Address --> 7 Bit with write */
	TWDR=copy_uint8SalveAddress<<1;
	/*Set write Bit Request in The LSB in Data Regsiter*/
	CLR_BIT(TWDR,0);
	/*Clear Start Condition*/
	CLR_BIT(TWCR,5);
	/*Clear interrupt TWI Flag*/
	SET_BIT(TWCR,7);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x18)
	{
		Loc_Error=SlaveAddressWriteError;
	}
	else
	{
		/*Do nothing*/
	}
	return Loc_Error;
}
/*TWI send SLave Address with Read*/
TWI_ErrorState MTWI_SendSalveAddressWithRead(uint8 copy_uint8SalveAddress)
{
	TWI_ErrorState Loc_Error=NoError;
	/*Send Salve Address --> 7 Bit with Read */
	TWDR=copy_uint8SalveAddress<<1;
	/*Set read Bit Request in The LSB in Data Regsiter*/
	SET_BIT(TWDR,0);
	/*Clear Start Condition*/
	CLR_BIT(TWCR,5);
	/*Clear interrupt TWI Flag*/
	SET_BIT(TWCR,7);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x40)
	{
		Loc_Error=SlaveAddressReadError;
	}
	else
	{
		/*Do nothing*/
	}
	return Loc_Error;
}
/*TWI send data as a master*/
TWI_ErrorState MTWI_MasterWriteDataByte(uint8 copy_uint8Data)
{
	TWI_ErrorState Loc_Error=NoError;
	/*Send Data */
	TWDR=copy_uint8Data;
	/*Clear interrupt TWI Flag*/
	SET_BIT(TWCR,7);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x28)
	{
		Loc_Error=MasterWriteByteError;
	}
	else
	{
		/*Do nothing*/
	}
	return Loc_Error;
}
/*TWI read data as a master*/
TWI_ErrorState MTWI_MasterReadDataByte(uint8 *copy_uint8Data)
{
	TWI_ErrorState Loc_Error=NoError;

	/*Clear interrupt TWI Flag*/
	SET_BIT(TWCR,7);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x50)
	{
		Loc_Error=MasterReadByteError;
	}
	else
	{
		*copy_uint8Data=TWDR;
	}
	return Loc_Error;
}

/*TWI Stop condition*/

void MTWI_SendStopCondtion(void)
{
	/*Send Stop Condition*/
	SET_BIT(TWCR,4);
	/*Clear TWI  interrupt flag*/
	SET_BIT(TWCR,7);
}
