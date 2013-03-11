################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/interconnect/ClientInterface.cpp \
../src/interconnect/Master.cpp \
../src/interconnect/TabletServer.cpp 

OBJS += \
./src/interconnect/ClientInterface.o \
./src/interconnect/Master.o \
./src/interconnect/TabletServer.o 

CPP_DEPS += \
./src/interconnect/ClientInterface.d \
./src/interconnect/Master.d \
./src/interconnect/TabletServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/interconnect/%.o: ../src/interconnect/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


