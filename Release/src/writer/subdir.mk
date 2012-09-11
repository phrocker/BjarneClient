################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/writer/MutationCollector.cpp \
../src/writer/Sink.cpp 

OBJS += \
./src/writer/MutationCollector.o \
./src/writer/Sink.o 

CPP_DEPS += \
./src/writer/MutationCollector.d \
./src/writer/Sink.d 


# Each subdirectory must supply rules for building sources it contributes
src/writer/%.o: ../src/writer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/thrift -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


