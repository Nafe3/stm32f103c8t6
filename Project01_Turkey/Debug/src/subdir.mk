################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Delay_program.c \
../src/GPIO.c \
../src/HCLCD.c \
../src/HLED.c \
../src/HSwitch_program.c \
../src/HUART_program.c \
../src/NVIC.c \
../src/RCC_program.c \
../src/SCHEDULAR_config.c \
../src/SCHEDULAR_program.c \
../src/SYSTICK_program.c \
../src/UART_program.c \
../src/main.c 

OBJS += \
./src/Delay_program.o \
./src/GPIO.o \
./src/HCLCD.o \
./src/HLED.o \
./src/HSwitch_program.o \
./src/HUART_program.o \
./src/NVIC.o \
./src/RCC_program.o \
./src/SCHEDULAR_config.o \
./src/SCHEDULAR_program.o \
./src/SYSTICK_program.o \
./src/UART_program.o \
./src/main.o 

C_DEPS += \
./src/Delay_program.d \
./src/GPIO.d \
./src/HCLCD.d \
./src/HLED.d \
./src/HSwitch_program.d \
./src/HUART_program.d \
./src/NVIC.d \
./src/RCC_program.d \
./src/SCHEDULAR_config.d \
./src/SCHEDULAR_program.d \
./src/SYSTICK_program.d \
./src/UART_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


