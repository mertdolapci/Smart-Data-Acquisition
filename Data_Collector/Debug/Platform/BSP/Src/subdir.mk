################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/BSP/Src/bsp_led.c \
../Platform/BSP/Src/bsp_runtime_counter.c \
../Platform/BSP/Src/bsp_uart.c 

OBJS += \
./Platform/BSP/Src/bsp_led.o \
./Platform/BSP/Src/bsp_runtime_counter.o \
./Platform/BSP/Src/bsp_uart.o 

C_DEPS += \
./Platform/BSP/Src/bsp_led.d \
./Platform/BSP/Src/bsp_runtime_counter.d \
./Platform/BSP/Src/bsp_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/BSP/Src/%.o Platform/BSP/Src/%.su Platform/BSP/Src/%.cyclo: ../Platform/BSP/Src/%.c Platform/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Include -I"C:/STM32F7_WS/Data_Collector/Platform/BSP/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Application/app_ctrl/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Services/Logging/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Application/task_monitoring/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Services/Monitoring/Inc" -I"C:/STM32F7_WS/Data_Collector/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Platform-2f-BSP-2f-Src

clean-Platform-2f-BSP-2f-Src:
	-$(RM) ./Platform/BSP/Src/bsp_led.cyclo ./Platform/BSP/Src/bsp_led.d ./Platform/BSP/Src/bsp_led.o ./Platform/BSP/Src/bsp_led.su ./Platform/BSP/Src/bsp_runtime_counter.cyclo ./Platform/BSP/Src/bsp_runtime_counter.d ./Platform/BSP/Src/bsp_runtime_counter.o ./Platform/BSP/Src/bsp_runtime_counter.su ./Platform/BSP/Src/bsp_uart.cyclo ./Platform/BSP/Src/bsp_uart.d ./Platform/BSP/Src/bsp_uart.o ./Platform/BSP/Src/bsp_uart.su

.PHONY: clean-Platform-2f-BSP-2f-Src

