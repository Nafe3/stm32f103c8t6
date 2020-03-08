################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DIO_program.c \
../src/KEYPAD_program.c \
../src/RCC_program.c \
../src/STK_program.c \
../src/mymain.c 

OBJS += \
./src/DIO_program.o \
./src/KEYPAD_program.o \
./src/RCC_program.o \
./src/STK_program.o \
./src/mymain.o 

C_DEPS += \
./src/DIO_program.d \
./src/KEYPAD_program.d \
./src/RCC_program.d \
./src/STK_program.d \
./src/mymain.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/DEVICE" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


