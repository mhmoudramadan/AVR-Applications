/*
 * MI2C_Private.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Dell
 */

#ifndef MCAL_MTWI_MI2C_PRIVATE_H_
#define MCAL_MTWI_MI2C_PRIVATE_H_

#define TWDR *((volatile uint8*)0x23)
#define TWAR *((volatile uint8*)0x22)
#define TWSR *((volatile uint8*)0x21)
#define TWCR *((volatile uint8*)0x56)
#define TWBR *((volatile uint8*)0x20)

#endif /* MCAL_MTWI_MI2C_PRIVATE_H_ */
