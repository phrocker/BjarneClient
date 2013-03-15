################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/scanner/constructs/Heuristic.cpp 

CC_SRCS += \
../src/scanner/constructs/testResults.cc 

OBJS += \
./src/scanner/constructs/Heuristic.o \
./src/scanner/constructs/testResults.o 

CC_DEPS += \
./src/scanner/constructs/testResults.d 

CPP_DEPS += \
./src/scanner/constructs/Heuristic.d 


# Each subdirectory must supply rules for building sources it contributes
src/scanner/constructs/%.o: ../src/scanner/constructs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/scanner/constructs/%.o: ../src/scanner/constructs/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


