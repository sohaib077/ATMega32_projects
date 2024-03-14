################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/TIMERS/subdir.mk
-include MCAL/PORT/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/STEPPER/subdir.mk
-include HAL/LCD/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
garage_system.lss \

FLASH_IMAGE += \
garage_system.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: garage_system.elf secondary-outputs

# Tool invocations
garage_system.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,garage_system.map -mmcu=atmega16 -o "garage_system.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

garage_system.lss: garage_system.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S garage_system.elf  >"garage_system.lss"
	@echo 'Finished building: $@'
	@echo ' '

garage_system.hex: garage_system.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex garage_system.elf  "garage_system.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: garage_system.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t garage_system.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) garage_system.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
