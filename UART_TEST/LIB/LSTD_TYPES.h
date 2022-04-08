
#ifndef LSTD_TYPES_H   //guard
#define LSTD_TYPES_H


typedef unsigned char uint8 ;  //or u8
typedef signed char sint8 ;    // or s8
   
typedef unsigned short int uint16 ;   //or u16
typedef signed short int sint16  ; //or u16

typedef unsigned long int uint32   ; 
typedef signed long int sint32   ;

typedef float f32 ;  //or 
typedef double f64 ;  // 3ashnn 8 byte

// error state

	typedef enum
{
	NOK,
	OK
	}ErrorState;

#endif
