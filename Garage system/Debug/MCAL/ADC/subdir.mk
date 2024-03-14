################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Embedded/Projects/Garage\ system/MCAL/ADC/ADC_program\ .c 

OBJS += \
./MCAL/ADC/ADC_program\ .o 

C_DEPS += \
./MCAL/ADC/ADC_program\ .d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/ADC/ADC_program\ .o: D:/Embedded/Projects/Garage\ system/MCAL/ADC/ADC_program\ .c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"MCAL/ADC/ADC_program .d" -MT"MCAL/ADC/ADC_program\ .d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


