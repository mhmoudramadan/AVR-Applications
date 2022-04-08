/*
 * MTIMER2_Interface.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTIMER2_MTIMER2_INTERFACE_H_
#define MCAL_MTIMER2_MTIMER2_INTERFACE_H_

void MTIMER2_VidInit(void);
void MTIMER2_VidSetPreLoad(uint8 copy_uint8PreLoadValue);
void MTIMER2_VidSetCTCRegister(uint8 copy_uint8CTCRegisteValue);
void MTIMER2_VidTIMER2_OVERFLOW_SetCallBack(void (*PtrToFun)(void));
void MTIMER2_VidTIMER2_CTC_SetCallBack(void (*PtrToFun)(void));
#endif /* MCAL_MTIMER2_MTIMER2_INTERFACE_H_ */
