#include "app_control.h"
#include "app_types.h"
#include "svc_log.h"
#include "bsp_led.h"
#include "cmsis_os2.h"

#include "lwip.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
extern struct netif gnetif;


static app_state_t app_state_init(void);
static app_state_t app_state_running(void);
static app_state_t app_state_error(void);

static app_state_t app_state_init(void)
{
    LOGI("APP_ST_INIT");

    bsp_led_init();
    svc_log_init();

    LOGI("Application init completed");

    return APP_ST_RUNNING;
}

static app_state_t app_state_running(void)
{
    static uint32_t alive_cnt = 0;
    static uint32_t last_measure_tick = 0;
    static uint32_t last_tx_tick = 0;

    uint32_t now = osKernelGetTickCount();

    bsp_led_toggle();
    LOGI("APP_ST_RUNNING alive=%lu", (unsigned long)alive_cnt++);

    if ((now - last_measure_tick) >= APP_MEASURE_PERIOD_MS)
    {
        last_measure_tick = now;

        LOGI("MEASURE tick");
        LOGI("IP      : %s", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
        LOGI("NETMASK : %s", ip4addr_ntoa(netif_ip4_netmask(&gnetif)));
        LOGI("GW      : %s", ip4addr_ntoa(netif_ip4_gw(&gnetif)));

        LOGI("Link    : %s",
             netif_is_link_up(&gnetif) ? "UP" : "DOWN");

        LOGI("NetIf   : %s",
             netif_is_up(&gnetif) ? "UP" : "DOWN");

        LOGI("Flags = 0x%04X", gnetif.flags);

        LOGI("HWADDR=%02X:%02X:%02X:%02X:%02X:%02X",
             gnetif.hwaddr[0],
             gnetif.hwaddr[1],
             gnetif.hwaddr[2],
             gnetif.hwaddr[3],
             gnetif.hwaddr[4],
             gnetif.hwaddr[5]);

        // Adım-4:
        // svc_sensor_read(&data);
        // svc_queue_push(&data);
    }

    if ((now - last_tx_tick) >= APP_TX_PERIOD_MS)
    {
        last_tx_tick = now;

        LOGI("TX tick");

        // Adım-6:
        // svc_http_send_batch();
    }

    osDelay(APP_HEARTBEAT_PERIOD_MS);

    return APP_ST_RUNNING;
}

static app_state_t app_state_error(void)
{
    LOGE("APP_ST_ERROR");

    osDelay(1000);

    return APP_ST_INIT;
}

void AppControlTask(void *argument)
{
    (void)argument;

    app_state_t state = APP_ST_INIT;

    LOGI("AppControlTask started");

    for (;;)
    {
        switch (state)
        {
        case APP_ST_INIT:
            state = app_state_init();
            break;

        case APP_ST_RUNNING:
            state = app_state_running();
            break;

        case APP_ST_ERROR:
        default:
            state = app_state_error();
            break;
        }
    }
}
