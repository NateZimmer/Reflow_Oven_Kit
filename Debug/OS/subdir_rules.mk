################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
OS/os.obj: ../OS/os.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -O2 -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="OS/os.pp" --obj_directory="OS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

OS/time.obj: ../OS/time.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -O2 -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="OS/time.pp" --obj_directory="OS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


