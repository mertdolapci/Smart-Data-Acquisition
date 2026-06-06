#include "bsp_uart.h"
#include "stm32f7xx_hal.h"

// CubeMX'in oluşturduğu UART handle ismi hangisiyse:
extern UART_HandleTypeDef huart1;

int bsp_uart_write(const uint8_t* data, size_t len)
{
    if (!data || len == 0) return 0;

    // Şimdilik blocking TX (demo için en hızlı).
    // Sonra DMA/IT'ye geçeriz.
    if (HAL_UART_Transmit(&huart1, (uint8_t*)data, (uint16_t)len, 50) == HAL_OK)
        return (int)len;

    return -1;
}
