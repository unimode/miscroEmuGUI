################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/paramra/workdir/miscroF411/Src/gui.c \
../src/miscroEmuGUI.c 

OBJS += \
./src/gui.o \
./src/miscroEmuGUI.o 

C_DEPS += \
./src/gui.d \
./src/miscroEmuGUI.d 


# Each subdirectory must supply rules for building sources it contributes
src/gui.o: /home/paramra/workdir/miscroF411/Src/gui.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/paramra/workdir/miscroF411/Inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/paramra/workdir/miscroF411/Inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


