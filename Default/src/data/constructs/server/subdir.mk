################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/constructs/server/RangeDefinition.cpp \
../src/data/constructs/server/ServerDefinition.cpp 

OBJS += \
./src/data/constructs/server/RangeDefinition.o \
./src/data/constructs/server/ServerDefinition.o 

CPP_DEPS += \
./src/data/constructs/server/RangeDefinition.d \
./src/data/constructs/server/ServerDefinition.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/constructs/server/%.o: ../src/data/constructs/server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


