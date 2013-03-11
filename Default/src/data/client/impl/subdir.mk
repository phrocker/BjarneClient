################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/client/impl/TabletServerLocator.cpp 

OBJS += \
./src/data/client/impl/TabletServerLocator.o 

CPP_DEPS += \
./src/data/client/impl/TabletServerLocator.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/client/impl/%.o: ../src/data/client/impl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


