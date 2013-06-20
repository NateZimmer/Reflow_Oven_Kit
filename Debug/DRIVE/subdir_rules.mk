################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DRIVE/led.obj: ../DRIVE/led.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="DRIVE/led.pp" --obj_directory="DRIVE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DRIVE/rtc.obj: ../DRIVE/rtc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="DRIVE/rtc.pp" --obj_directory="DRIVE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DRIVE/spi.obj: ../DRIVE/spi.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="DRIVE/spi.pp" --obj_directory="DRIVE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DRIVE/timer.obj: ../DRIVE/timer.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"F:/Program Files/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="F:/Program Files/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/Program Files/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="DRIVE/timer.pp" --obj_directory="DRIVE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


