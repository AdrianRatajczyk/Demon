################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADXL343.c \
../src/LIS3DH.c \
../src/LM9DS0.c \
../src/MMA9551L.c \
../src/autokorelacja.c \
../src/fifo.c \
../src/fifo2.c \
../src/main.c \
../src/pomiar.c \
../src/spi.c \
../src/uart.c 

OBJS += \
./src/ADXL343.o \
./src/LIS3DH.o \
./src/LM9DS0.o \
./src/MMA9551L.o \
./src/autokorelacja.o \
./src/fifo.o \
./src/fifo2.o \
./src/main.o \
./src/pomiar.o \
./src/spi.o \
./src/uart.o 

C_DEPS += \
./src/ADXL343.d \
./src/LIS3DH.d \
./src/LM9DS0.d \
./src/MMA9551L.d \
./src/autokorelacja.d \
./src/fifo.d \
./src/fifo2.d \
./src/main.d \
./src/pomiar.d \
./src/spi.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DSTM32F10X_CL -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DDEBUG -I"../include" -I"../libs/CMSIS/include" -I"../libs/StdPeriph/include" -I"../libs/misc/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


