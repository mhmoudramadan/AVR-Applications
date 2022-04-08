/*
 * HSTTEPPER_Config.h
 *
 *  Created on: Jan 29, 2022
 *      Author: Dell
 */

#ifndef HAL_HSTEPPER_HSTEPPER_CONFIG_H_
#define HAL_HSTEPPER_HSTEPPER_CONFIG_H_

/*option Step angle
 * 1-HALFSTEP
 * 2-FULLSTEP
 * 3-MICROSTEP*/

#define STEP_ANGLE FULLSTEP

#define MAX_SPEED   15
#define MIN_SPEED   10
#define MAX_SPEED_DELAY 7


#define STEPPER_PORT  MDIO_PORTC

#define STEPPER_COIL1  PIN3
#define STEPPER_COIL2  PIN4
#define STEPPER_COIL3  PIN5
#define STEPPER_COIL4  PIN6



#endif /* HAL_HSTEPPER_HSTEPPER_CONFIG_H_ */
