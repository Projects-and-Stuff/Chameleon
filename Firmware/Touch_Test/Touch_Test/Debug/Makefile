################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/QTouch/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../src/QTouch/BitBangSPI_Master.c \
../src/QTouch/init_mcu_attiny84.c \
../src/QTouch/eeprom_access.c \
../src/QTouch/QDebug.c \
../src/QTouch/QDebugTransport.c \
../touch.c


PREPROCESSING_SRCS +=  \
../i2cmaster.S \
../src/QTouch/qm_asm_tiny_mega.s


ASM_SRCS += 


OBJS +=  \
i2cmaster.o \
main.o \
src/QTouch/BitBangSPI_Master.o \
src/QTouch/init_mcu_attiny84.o \
src/QTouch/eeprom_access.o \
src/QTouch/QDebug.o \
src/QTouch/QDebugTransport.o \
src/QTouch/qm_asm_tiny_mega.o \
touch.o


OBJS_AS_ARGS +=  \
i2cmaster.o \
main.o \
src/QTouch/BitBangSPI_Master.o \
src/QTouch/init_mcu_attiny84.o \
src/QTouch/eeprom_access.o \
src/QTouch/QDebug.o \
src/QTouch/QDebugTransport.o \
src/QTouch/qm_asm_tiny_mega.o \
touch.o


C_DEPS +=  \
main.d \
src/QTouch/BitBangSPI_Master.d \
src/QTouch/init_mcu_attiny84.d \
src/QTouch/eeprom_access.d \
src/QTouch/QDebug.d \
src/QTouch/QDebugTransport.d \
touch.d


C_DEPS_AS_ARGS +=  \
main.d \
src/QTouch/BitBangSPI_Master.d \
src/QTouch/init_mcu_attiny84.d \
src/QTouch/eeprom_access.d \
src/QTouch/QDebug.d \
src/QTouch/QDebugTransport.d \
touch.d


OUTPUT_FILE_PATH +=Touch_Test.elf

OUTPUT_FILE_PATH_AS_ARGS +=Touch_Test.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=8000000UL  -I"../src/QTouch" -I".."  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=attiny84   -o"$@" "$<" 
	@echo Finished building: $<

src/QTouch/%.o: ../src/QTouch/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=8000000UL  -I"../src/QTouch" -I".."  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=attiny84   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
./i2cmaster.o: .././i2cmaster.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny84   -o"$@" "$<"
	@echo Finished building: $<

src/QTouch/qm_asm_tiny_mega.o: ../src/QTouch/qm_asm_tiny_mega.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny84   -o"$@" "$<"
	@echo Finished building: $<


./%.o: .././%.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny84   -o"$@" "$<"
	@echo Finished building: $<

src/QTouch/%.o: ../src/QTouch/%.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny84   -o"$@" "$<"
	@echo Finished building: $<




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Touch_Test.map" -Wl,--start-group -Wl,-lm -Wl,-lavr25g1s0_4qm_4x_1y_k_0rs  -Wl,--end-group -Wl,-L"../src/QTouch"   -mmcu=attiny84  
	@echo Finished building target: $@
	"C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Touch_Test.elf" "Touch_Test.hex"
	"C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Touch_Test.elf" "Touch_Test.eep" || exit 0
	"C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objdump.exe" -h -S "Touch_Test.elf" > "Touch_Test.lss"
	"C:\Program Files\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-size.exe" "Touch_Test.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Touch_Test.elf" "Touch_Test.a" "Touch_Test.hex" "Touch_Test.lss" "Touch_Test.eep" "Touch_Test.map"
	