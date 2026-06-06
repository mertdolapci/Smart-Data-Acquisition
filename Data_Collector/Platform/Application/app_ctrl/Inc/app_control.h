#pragma once
#include "cmsis_os2.h"


#define APP_HEARTBEAT_PERIOD_MS   (1000u)
#define APP_MEASURE_PERIOD_MS     (5000u)
#define APP_TX_PERIOD_MS          (30000u)


void AppControlTask(void *argument);
