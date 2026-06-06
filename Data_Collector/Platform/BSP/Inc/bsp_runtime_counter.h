#pragma once
#include <stdint.h>

uint8_t BspRuntimeCounter_Init(void);
uint32_t BspRuntimeCounter_Get(void);
uint8_t BspRuntimeCounter_IsEnabled(void);
