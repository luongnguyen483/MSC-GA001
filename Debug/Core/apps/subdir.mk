################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/apps/Buzzer.c \
../Core/apps/appMain.c \
../Core/apps/keypad_display.c \
../Core/apps/leds.c \
../Core/apps/switches.c \
../Core/apps/timebasetimer.c 

OBJS += \
./Core/apps/Buzzer.o \
./Core/apps/appMain.o \
./Core/apps/keypad_display.o \
./Core/apps/leds.o \
./Core/apps/switches.o \
./Core/apps/timebasetimer.o 

C_DEPS += \
./Core/apps/Buzzer.d \
./Core/apps/appMain.d \
./Core/apps/keypad_display.d \
./Core/apps/leds.d \
./Core/apps/switches.d \
./Core/apps/timebasetimer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/apps/%.o: ../Core/apps/%.c Core/apps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F413xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

