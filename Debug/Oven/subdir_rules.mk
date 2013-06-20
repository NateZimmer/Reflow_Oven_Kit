################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Oven/oven.obj: ../Oven/oven.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Oven/oven.pp" --obj_directory="Oven" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Oven/oven_control.obj: ../Oven/oven_control.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Oven/oven_control.pp" --obj_directory="Oven" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Oven/profile_lead.obj: ../Oven/profile_lead.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Oven/profile_lead.pp" --obj_directory="Oven" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Oven/profile_pb_free.obj: ../Oven/profile_pb_free.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Oven/profile_pb_free.pp" --obj_directory="Oven" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


