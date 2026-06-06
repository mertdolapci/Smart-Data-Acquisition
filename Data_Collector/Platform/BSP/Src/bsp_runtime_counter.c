#include "bsp_runtime_counter.h"
#include "stm32f7xx.h"


/*
 * ARM Cortex-M DWT Lock Access Register.
 * Address and unlock key are defined by ARM TRM.
 */
#define DWT_LAR_ADDRESS  ((volatile uint32_t*)0xE0001FB0u)
#define DWT_LAR_KEY      (0xC5ACCE55u)

uint8_t BspRuntimeCounter_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /*
     * Some Cortex-M7 implementations require unlocking DWT.
     * Safe to try in debug/profiling context.
     */
    *DWT_LAR_ADDRESS = DWT_LAR_KEY;

    DWT->CYCCNT = 0u;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    return BspRuntimeCounter_IsEnabled();
}

uint32_t BspRuntimeCounter_Get(void)
{
    return DWT->CYCCNT;
}

uint8_t BspRuntimeCounter_IsEnabled(void)
{
    return ((DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk) != 0u) ? 1u : 0u;
}
