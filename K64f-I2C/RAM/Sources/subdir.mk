################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/I2CDriver.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/I2CDriver.c \
../Sources/main.c \

OBJS += \
./Sources/I2CDriver.o \
./Sources/main.o \

C_DEPS += \
./Sources/I2CDriver.d \
./Sources/main.d \

OBJS_QUOTED += \
"./Sources/I2CDriver.o" \
"./Sources/main.o" \

C_DEPS_QUOTED += \
"./Sources/I2CDriver.d" \
"./Sources/main.d" \

OBJS_OS_FORMAT += \
./Sources/I2CDriver.o \
./Sources/main.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/I2CDriver.o: ../Sources/I2CDriver.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/I2CDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/I2CDriver.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '


