################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/client/ExtentLocator.cpp \
../src/data/client/TabletLocation.cpp \
../src/data/client/TabletLocationObtainer.cpp 

OBJS += \
./src/data/client/ExtentLocator.o \
./src/data/client/TabletLocation.o \
./src/data/client/TabletLocationObtainer.o 

CPP_DEPS += \
./src/data/client/ExtentLocator.d \
./src/data/client/TabletLocation.d \
./src/data/client/TabletLocationObtainer.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/client/%.o: ../src/data/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


