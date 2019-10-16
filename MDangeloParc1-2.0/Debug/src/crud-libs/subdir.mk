################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/crud-libs/CrudCustomers.c \
../src/crud-libs/CrudOrders.c 

OBJS += \
./src/crud-libs/CrudCustomers.o \
./src/crud-libs/CrudOrders.o 

C_DEPS += \
./src/crud-libs/CrudCustomers.d \
./src/crud-libs/CrudOrders.d 


# Each subdirectory must supply rules for building sources it contributes
src/crud-libs/%.o: ../src/crud-libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


