################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/data/streaming/byte_stream.cpp \
../src/data/streaming/data_out_stream.cpp \
../src/data/streaming/dataoutstream.cpp \
../src/data/streaming/stream_ifc.cpp \
../src/data/streaming/translator.cpp 

OBJS += \
./src/data/streaming/byte_stream.o \
./src/data/streaming/data_out_stream.o \
./src/data/streaming/dataoutstream.o \
./src/data/streaming/stream_ifc.o \
./src/data/streaming/translator.o 

CPP_DEPS += \
./src/data/streaming/byte_stream.d \
./src/data/streaming/data_out_stream.d \
./src/data/streaming/dataoutstream.d \
./src/data/streaming/stream_ifc.d \
./src/data/streaming/translator.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/streaming/%.o: ../src/data/streaming/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


