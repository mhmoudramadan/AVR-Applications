/*
 * MSPI_Private.h
 *
 *  Created on: Feb 26, 2022
 *      Author: Dell
 */

#ifndef MCAL_MSPI_MSPI_PRIVATE_H_
#define MCAL_MSPI_MSPI_PRIVATE_H_

#define SPCR  *((volatile uint8*)0x2D)
#define SPSR  *((volatile uint8*)0x2E)
#define SPDR  *((volatile uint8*)0x2F)


#define MSPI_LSB_DATAORDER   0
#define MSPI_MSB_DATAORDER   1

#define MSPI_RISING_POLARITY  0
#define MSPI_FALLING_POLARITY 1

#define MSPI_SETUP_PHASE   0
#define MSPI_SAMPLE_PHASE  1

#define MSPI_DOUBLESPEED     0
#define MSPI_NO_DOUBLESPEED  1

#define MSPI_PRESCALER_4_NODOUBLE     0
#define MSPI_PRESCALER_16_NODOUBLE    1
#define MSPI_PRESCALER_64_NODOUBLE    2
#define MSPI_PRESCALER_128_NODOUBLE   3
#define MSPI_PRESCALER_2_Double       4
#define MSPI_PRESCALER_8_Double       5
#define MSPI_PRESCALER_32_Double      6
#define MSPI_PRESCALER_64_Double      7
#endif /* MCAL_MSPI_MSPI_PRIVATE_H_ */
