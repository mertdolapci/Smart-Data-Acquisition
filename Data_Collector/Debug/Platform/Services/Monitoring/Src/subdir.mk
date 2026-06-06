################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/Services/Monitoring/Src/svc_monitoring.c 

OBJS += \
./Platform/Services/Monitoring/Src/svc_monitoring.o 

C_DEPS += \
./Platform/Services/Monitoring/Src/svc_monitoring.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/Services/Monitoring/Src/%.o Platform/Services/Monitoring/Src/%.su Platform/Services/Monitoring/Src/%.cyclo: ../Platform/Services/Monitoring/Src/%.c Platform/Services/Monitoring/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Include -I"C:/STM32F7_WS/Data_Collector/Platform/BSP/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Application/app_ctrl/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Services/Logging/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Application/task_monitoring/Inc" -I"C:/STM32F7_WS/Data_Collector/Platform/Services/Monitoring/Inc" -I"C:/STM32F7_WS/Data_Collector/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Platform-2f-Services-2f-Monitoring-2f-Src

clean-Platform-2f-Services-2f-Monitoring-2f-Src:
	-$(RM) ./Platform/Services/Monitoring/Src/svc_monitoring.cyclo ./Platform/Services/Monitoring/Src/svc_monitoring.d ./Platform/Services/Monitoring/Src/svc_monitoring.o ./Platform/Services/Monitoring/Src/svc_monitoring.su

.PHONY: clean-Platform-2f-Services-2f-Monitoring-2f-Src

