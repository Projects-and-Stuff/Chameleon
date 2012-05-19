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
../src/QTouch/init_mcu_attiny44.c \
../src/QTouch/eeprom_access.c \
../src/QTouch/QDebug.c \
../src/QTouch/QDebugTransport.c \
../touch.c


PREPROCESSING_SRCS +=  \
../src/QTouch/qm_asm_tiny_mega.s


ASM_SRCS += 


OBJS +=  \
main.o \
src/QTouch/BitBangSPI_Master.o \
src/QTouch/init_mcu_attiny44.o \
src/QTouch/eeprom_access.o \
src/QTouch/QDebug.o \
src/QTouch/QDebugTransport.o \
src/QTouch/qm_asm_tiny_mega.o \
touch.o


OBJS_AS_ARGS +=  \
main.o \
src/QTouch/BitBangSPI_Master.o \
src/QTouch/init_mcu_attiny44.o \
src/QTouch/eeprom_access.o \
src/QTouch/QDebug.o \
src/QTouch/QDebugTransport.o \
src/QTouch/qm_asm_tiny_mega.o \
touch.o


C_DEPS +=  \
main.d \
src/QTouch/BitBangSPI_Master.d \
src/QTouch/init_mcu_attiny44.d \
src/QTouch/eeprom_access.d \
src/QTouch/QDebug.d \
src/QTouch/QDebugTransport.d \
touch.d


C_DEPS_AS_ARGS +=  \
main.d \
src/QTouch/BitBangSPI_Master.d \
src/QTouch/init_mcu_attiny44.d \
src/QTouch/eeprom_access.d \
src/QTouch/QDebug.d \
src/QTouch/QDebugTransport.d \
touch.d


OUTPUT_FILE_PATH +=Chameleon.elf

OUTPUT_FILE_PATH_AS_ARGS +=Chameleon.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -I"../src/QTouch" -I".."  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=attiny44a   -o"$@" "$<" 
	@echo Finished building: $<

src/QTouch/%.o: ../src/QTouch/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -I"../src/QTouch" -I".."  -Os -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=attiny44a   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
src/QTouch/qm_asm_tiny_mega.o: ../src/QTouch/qm_asm_tiny_mega.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny44a   -o"$@" "$<"
	@echo Finished building: $<


src/QTouch/%.o: ../src/QTouch/%.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : (AVR_8_bit_GNU_Toolchain_3.4.0_663) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -I "../src/QTouch" -I ".."  -Wa,-g  -mmcu=attiny44a   -o"$@" "$<"
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
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Chameleon.map" -Wl,--start-group -Wl,-lm -Wl,-lavr25g1s0_4qm_4x_1y_k_0rs  -Wl,--end-group -Wl,-L"../src/QTouch"   -mmcu=attiny44a  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Chameleon.elf" "Chameleon.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Chameleon.elf" "Chameleon.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-objdump.exe" -h -S "Chameleon.elf" > "Chameleon.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.0.65\AVRToolchain\bin\avr-size.exe" "Chameleon.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Chameleon.elf" "Chameleon.a" "Chameleon.hex" "Chameleon.lss" "Chameleon.eep" "Chameleon.map"
	