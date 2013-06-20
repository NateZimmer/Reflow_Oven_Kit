################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/Program Files/ti/ccsv5/tools/compiler/msp430

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./DRIVE/timer.obj" \
"./DRIVE/spi.obj" \
"./DRIVE/rtc.obj" \
"./DRIVE/led.obj" \
"./LCD/touch.obj" \
"./LCD/gui.obj" \
"./LCD/colorLCD.obj" \
"./OS/time.obj" \
"./OS/os.obj" \
"./Oven/profile_pb_free.obj" \
"./Oven/profile_lead.obj" \
"./Oven/oven_control.obj" \
"./Oven/oven.obj" \
"./main.obj" \
-l"libc.a" \
"../lnk_msp430g2553.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Oven/subdir_vars.mk
-include OS/subdir_vars.mk
-include LCD/subdir_vars.mk
-include DRIVE/subdir_vars.mk
-include subdir_rules.mk
-include Oven/subdir_rules.mk
-include OS/subdir_rules.mk
-include LCD/subdir_rules.mk
-include DRIVE/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Reflow_Oven_Kit.out

# Tool invocations
Reflow_Oven_Kit.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal -z -m"Reflow_Oven_Kit.map" --stack_size=80 --heap_size=80 -i"F:/Program Files/ti/ccsv5/ccs_base/msp430/include" -i"F:/Program Files/ti/ccsv5/tools/compiler/msp430/lib" -i"F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --reread_libs --warn_sections --rom_model -o "Reflow_Oven_Kit.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "Reflow_Oven_Kit.out"
	-$(RM) "main.pp" "Oven\oven.pp" "Oven\oven_control.pp" "Oven\profile_lead.pp" "Oven\profile_pb_free.pp" "OS\os.pp" "OS\time.pp" "LCD\colorLCD.pp" "LCD\gui.pp" "LCD\touch.pp" "DRIVE\led.pp" "DRIVE\rtc.pp" "DRIVE\spi.pp" "DRIVE\timer.pp" 
	-$(RM) "main.obj" "Oven\oven.obj" "Oven\oven_control.obj" "Oven\profile_lead.obj" "Oven\profile_pb_free.obj" "OS\os.obj" "OS\time.obj" "LCD\colorLCD.obj" "LCD\gui.obj" "LCD\touch.obj" "DRIVE\led.obj" "DRIVE\rtc.obj" "DRIVE\spi.obj" "DRIVE\timer.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
