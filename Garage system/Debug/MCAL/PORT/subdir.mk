################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Embedded/Projects/Garage\ system/MCAL/PORT/PORT_prgram.c 

OBJS += \
./MCAL/PORT/PORT_prgram.o 

C_DEPS += \
./MCAL/PORT/PORT_prgram.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PORT/PORT_prgram.o: D:/Embedded/Projects/Garage\ system/MCAL/PORT/PORT_prgram.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


