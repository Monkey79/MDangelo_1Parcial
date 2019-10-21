################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/commons-libs/InfoMng.c \
../src/commons-libs/MenuBuilder.c \
../src/commons-libs/PrintHelper.c \
../src/commons-libs/Utils.c 

OBJS += \
./src/commons-libs/InfoMng.o \
./src/commons-libs/MenuBuilder.o \
./src/commons-libs/PrintHelper.o \
./src/commons-libs/Utils.o 

C_DEPS += \
./src/commons-libs/InfoMng.d \
./src/commons-libs/MenuBuilder.d \
./src/commons-libs/PrintHelper.d \
./src/commons-libs/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/commons-libs/%.o: ../src/commons-libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


