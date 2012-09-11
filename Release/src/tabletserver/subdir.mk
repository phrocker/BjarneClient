################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tabletserver/ExtentLocator.cpp 

OBJS += \
./src/tabletserver/ExtentLocator.o 

CPP_DEPS += \
./src/tabletserver/ExtentLocator.d 


# Each subdirectory must supply rules for building sources it contributes
src/tabletserver/%.o: ../src/tabletserver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/thrift -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


