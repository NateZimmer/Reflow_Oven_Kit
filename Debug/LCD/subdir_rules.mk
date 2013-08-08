################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LCD/colorLCD.obj: ../LCD/colorLCD.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -O2 -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="LCD/colorLCD.pp" --obj_directory="LCD" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCD/gui.obj: ../LCD/gui.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -O2 -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="LCD/gui.pp" --obj_directory="LCD" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

LCD/touch.obj: ../LCD/touch.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -O2 -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="LCD/touch.pp" --obj_directory="LCD" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


