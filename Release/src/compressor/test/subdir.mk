################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/compressor/test/zlibTest.c 

OBJS += \
./src/compressor/test/zlibTest.o 

C_DEPS += \
./src/compressor/test/zlibTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/compressor/test/%.o: ../src/compressor/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


