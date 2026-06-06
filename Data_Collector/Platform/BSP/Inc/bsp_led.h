#pragma once
#include <stdint.h>

void bsp_led_init(void);
void bsp_led_set(uint8_t on);
void bsp_led_toggle(void);
