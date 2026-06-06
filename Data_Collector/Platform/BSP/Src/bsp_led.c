#include "bsp_led.h"
#include "main.h"
#include "stm32f7xx_hal.h"

void bsp_led_init(void)
{
    // GPIO init CubeMX tarafından yapılıyor varsayıyoruz.
}

void bsp_led_set(uint8_t on)
{
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void bsp_led_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
}
