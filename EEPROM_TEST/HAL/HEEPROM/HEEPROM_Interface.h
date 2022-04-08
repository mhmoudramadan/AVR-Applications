/*
 * HEPPROM_Interface.h
 *
 *  Created on: Mar 11, 2022
 *      Author: Dell
 */

#ifndef HAL_HEEPROM_HEEPROM_INTERFACE_H_
#define HAL_HEEPROM_HEEPROM_INTERFACE_H_

void HEEPROM_VidSendDataByte(uint8 copy_uint8PageNumber,uint8 copy_uint8LocationAddress, uint8 copy_uint8Data);
uint8 HEEPROM_VidReadDataByte(uint8 copy_uint8PageNumber,uint8 copy_uint8LocationAddress);

#endif /* HAL_HEEPROM_HEEPROM_INTERFACE_H_ */
