#include "svc_log.h"
#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>
#include "cmsis_os2.h"


void svc_log_init(void)
{

}

static const char* lvl_str(log_level_t lvl)
{
    switch (lvl) {
    case LOG_LVL_INFO: return "INFO";
    case LOG_LVL_WARN: return "WARN";
    case LOG_LVL_ERR:  return "ERROR";
    default:           return "?";
    }
}

void svc_log(log_level_t lvl, const char* fmt, ...)
{
    char buf[512];

    int n = snprintf(buf, sizeof(buf), "[%s] ", lvl_str(lvl));
    if (n < 0) return;

    uint32_t tick = osKernelGetTickCount();
    uint32_t sec = tick / 1000u;
    uint32_t ms  = tick % 1000u;

    int k = snprintf(buf + (size_t)n,
             sizeof(buf),
             "[%05lu.%03lu] ",
             sec,
             ms);
    if (k < 0) return;

    va_list ap;
    va_start(ap, fmt);

    int m = vsnprintf(buf + (size_t)n + (size_t)k, sizeof(buf) - (size_t)n - (size_t)k, fmt, ap);
    va_end(ap);

    if (m < 0) return;

    size_t total = (size_t)n + (size_t)m + (size_t)k;
    if (total >= sizeof(buf)) total = sizeof(buf) - 1;

    if (total < sizeof(buf) - 2) {
        buf[total++] = '\r';
        buf[total++] = '\n';
        buf[total] = '\0';
    }

    (void)bsp_uart_write((const uint8_t*)buf, total);
}
