################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/core/timer_test.cpp 

OBJS += \
./test/core/timer_test.o 

CPP_DEPS += \
./test/core/timer_test.d 


# Each subdirectory must supply rules for building sources it contributes
test/core/%.o: ../test/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/bill/workspace/Jounce/contrib" -I"/home/bill/workspace/Jounce/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


