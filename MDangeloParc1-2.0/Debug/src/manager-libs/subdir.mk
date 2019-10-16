################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/manager-libs/MngCustomers.c \
../src/manager-libs/MngOrders.c 

OBJS += \
./src/manager-libs/MngCustomers.o \
./src/manager-libs/MngOrders.o 

C_DEPS += \
./src/manager-libs/MngCustomers.d \
./src/manager-libs/MngOrders.d 


# Each subdirectory must supply rules for building sources it contributes
src/manager-libs/%.o: ../src/manager-libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


