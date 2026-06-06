#pragma once
#include <stddef.h>
#include <stdint.h>

int bsp_uart_write(const uint8_t* data, size_t len);
