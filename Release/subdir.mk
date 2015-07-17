################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AllegroStepper.cpp \
../geometry.cpp \
../simplepolargraph.cpp 

OBJS += \
./AllegroStepper.o \
./geometry.o \
./simplepolargraph.o 

CPP_DEPS += \
./AllegroStepper.d \
./geometry.d \
./simplepolargraph.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Program Files\Arduino\hardware\arduino\cores\arduino" -I"C:\Program Files\Arduino\hardware\arduino\variants\mega" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105-r2 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


