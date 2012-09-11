################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/data-streams/data_writer.cpp \
../src/data/data-streams/dataoutstream.cpp 

OBJS += \
./src/data/data-streams/data_writer.o \
./src/data/data-streams/dataoutstream.o 

CPP_DEPS += \
./src/data/data-streams/data_writer.d \
./src/data/data-streams/dataoutstream.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/data-streams/%.o: ../src/data/data-streams/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/thrift -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


