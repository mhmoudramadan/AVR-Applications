/*
 * HSTEPPER_Interface.h
 *
 *  Created on: Jan 29, 2022
 *      Author: Dell
 */

#ifndef HAL_HSTEPPER_HSTEPPER_INTERFACE_H_
#define HAL_HSTEPPER_HSTEPPER_INTERFACE_H_

#define CW 0
#define CCW 1

#define HALFSTEP 0.0878
#define FULLSTEP 0.167
#define MICROSTEP  0

#define FREQ_OUT_TRACTION  1000
#define FREQ_in_TRACTION   600

#define REV_DISTANCE  0.7

void HStepper_Init(void);
void HStepper_SetStepsDirection(uint16 copy_uint16Steps,uint8 copy_uint8Direction);
void HStepper_SetSpeedDirection(uint16 copy_uint16Speed,uint8 copy_uint8Direction);

#endif /* HAL_HSTEPPER_HSTEPPER_INTERFACE_H_ */
