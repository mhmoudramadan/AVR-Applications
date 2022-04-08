################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/MTWI=MI2C/MI2C_Program.c 

OBJS += \
./MCAL/MTWI=MI2C/MI2C_Program.o 

C_DEPS += \
./MCAL/MTWI=MI2C/MI2C_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/MTWI=MI2C/MI2C_Program.o: ../MCAL/MTWI=MI2C/MI2C_Program.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"MCAL/MTWI=MI2C/MI2C_Program.d" -MT"MCAL/MTWI=MI2C/MI2C_Program.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


