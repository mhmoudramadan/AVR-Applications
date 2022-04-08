// SET& Clear & Get & toggle  --fun like macro
// guard


#ifndef LBIT_MATH_H

#define LBIT_MATH_H


#define SET_BIT(VAR,BIT_NUM) VAR|=(1<<BIT_NUM)

#define CLR_BIT(VAR,BIT_NUM) VAR&=(~(1<<BIT_NUM))

#define GET_BIT(VAR,BIT_NUM) ((VAR>>BIT_NUM)&0x01)  //0x01=1

#define TOGGLE_BIT(VAR,BIT_NUM) VAR^=(1<<BIT_NUM)

#endif
