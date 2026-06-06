#include "svc_log.h"
#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>

void svc_log_init(void)
{
    // Şimdilik boş. Sonra timestamp vb eklenebilir.
}

static const char* lvl_str(log_level_t lvl)
{
    switch (lvl) {
    case LOG_LVL_INFO: return "I";
    case LOG_LVL_WARN: return "W";
    case LOG_LVL_ERR:  return "E";
    default:           return "?";
    }
}

void svc_log(log_level_t lvl, const char* fmt, ...)
{
    char buf[256];

    int n = snprintf(buf, sizeof(buf), "[%s] ", lvl_str(lvl));
    if (n < 0) return;

    va_list ap;
    va_start(ap, fmt);
    int m = vsnprintf(buf + (size_t)n, sizeof(buf) - (size_t)n, fmt, ap);
    va_end(ap);

    if (m < 0) return;

    size_t total = (size_t)n + (size_t)m;
    if (total >= sizeof(buf)) total = sizeof(buf) - 1;

    // satır sonu
    if (total < sizeof(buf) - 2) {
        buf[total++] = '\r';
        buf[total++] = '\n';
        buf[total] = '\0';
    }

    (void)bsp_uart_write((const uint8_t*)buf, total);
}
