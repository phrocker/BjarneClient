################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/scanner/constructs/testResults.cc 

OBJS += \
./src/scanner/constructs/testResults.o 

CC_DEPS += \
./src/scanner/constructs/testResults.d 


# Each subdirectory must supply rules for building sources it contributes
src/scanner/constructs/%.o: ../src/scanner/constructs/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


