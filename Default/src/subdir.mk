################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientService.cpp \
../src/ClientService_server.skeleton.cpp \
../src/GCMonitorService.cpp \
../src/GCMonitorService_server.skeleton.cpp \
../src/Master.cpp \
../src/MasterClient.cpp \
../src/MasterClientService.cpp \
../src/MasterClientService_server.skeleton.cpp \
../src/MutationLogger.cpp \
../src/MutationLogger_server.skeleton.cpp \
../src/Results.cpp \
../src/SpanReceiver.cpp \
../src/SpanReceiver_server.skeleton.cpp \
../src/TabletClientService.cpp \
../src/TabletClientService_server.skeleton.cpp \
../src/TestService.cpp \
../src/TestService_server.skeleton.cpp \
../src/client_constants.cpp \
../src/client_types.cpp \
../src/cloudtrace_constants.cpp \
../src/cloudtrace_types.cpp \
../src/data_constants.cpp \
../src/data_types.cpp \
../src/gc_constants.cpp \
../src/gc_types.cpp \
../src/master_constants.cpp \
../src/master_types.cpp \
../src/security_constants.cpp \
../src/security_types.cpp \
../src/tabletserver_constants.cpp \
../src/tabletserver_types.cpp \
../src/test.cpp 

C_SRCS += \
../src/tablet_man_test.c 

OBJS += \
./src/ClientService.o \
./src/ClientService_server.skeleton.o \
./src/GCMonitorService.o \
./src/GCMonitorService_server.skeleton.o \
./src/Master.o \
./src/MasterClient.o \
./src/MasterClientService.o \
./src/MasterClientService_server.skeleton.o \
./src/MutationLogger.o \
./src/MutationLogger_server.skeleton.o \
./src/Results.o \
./src/SpanReceiver.o \
./src/SpanReceiver_server.skeleton.o \
./src/TabletClientService.o \
./src/TabletClientService_server.skeleton.o \
./src/TestService.o \
./src/TestService_server.skeleton.o \
./src/client_constants.o \
./src/client_types.o \
./src/cloudtrace_constants.o \
./src/cloudtrace_types.o \
./src/data_constants.o \
./src/data_types.o \
./src/gc_constants.o \
./src/gc_types.o \
./src/master_constants.o \
./src/master_types.o \
./src/security_constants.o \
./src/security_types.o \
./src/tablet_man_test.o \
./src/tabletserver_constants.o \
./src/tabletserver_types.o \
./src/test.o 

C_DEPS += \
./src/tablet_man_test.d 

CPP_DEPS += \
./src/ClientService.d \
./src/ClientService_server.skeleton.d \
./src/GCMonitorService.d \
./src/GCMonitorService_server.skeleton.d \
./src/Master.d \
./src/MasterClient.d \
./src/MasterClientService.d \
./src/MasterClientService_server.skeleton.d \
./src/MutationLogger.d \
./src/MutationLogger_server.skeleton.d \
./src/Results.d \
./src/SpanReceiver.d \
./src/SpanReceiver_server.skeleton.d \
./src/TabletClientService.d \
./src/TabletClientService_server.skeleton.d \
./src/TestService.d \
./src/TestService_server.skeleton.d \
./src/client_constants.d \
./src/client_types.d \
./src/cloudtrace_constants.d \
./src/cloudtrace_types.d \
./src/data_constants.d \
./src/data_types.d \
./src/gc_constants.d \
./src/gc_types.d \
./src/master_constants.d \
./src/master_types.d \
./src/security_constants.d \
./src/security_types.d \
./src/tabletserver_constants.d \
./src/tabletserver_types.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/local/include/thrift -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


