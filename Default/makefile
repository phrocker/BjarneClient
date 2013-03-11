################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include src/writer/subdir.mk
-include src/scanner/impl/subdir.mk
-include src/scanner/constructs/subdir.mk
-include src/scanner/subdir.mk
-include src/interconnect/subdir.mk
-include src/data/streaming/subdir.mk
-include src/data/constructs/server/subdir.mk
-include src/data/constructs/security/subdir.mk
-include src/data/constructs/configuration/subdir.mk
-include src/data/constructs/client/zookeeper/subdir.mk
-include src/data/constructs/client/subdir.mk
-include src/data/constructs/subdir.mk
-include src/data/client/impl/metadata/subdir.mk
-include src/data/client/impl/subdir.mk
-include src/data/client/subdir.mk
-include src/data/subdir.mk
-include src/connector/impl/test/subdir.mk
-include src/connector/impl/subdir.mk
-include src/connector/subdir.mk
-include src/subdir.mk
-include obj/Debug/src/scanner/constructs/subdir.mk
-include obj/Debug/src/data/constructs/configuration/subdir.mk
-include build/CMakeFiles/CompilerIdCXX/subdir.mk
-include build/CMakeFiles/CompilerIdC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BjarneClient

# Tool invocations
BjarneClient: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "BjarneClient" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) BjarneClient
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
