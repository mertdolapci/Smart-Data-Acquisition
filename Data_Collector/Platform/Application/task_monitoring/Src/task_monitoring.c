#include "task_monitoring.h"
#include "task_monitoring_cfg.h"
#include "cmsis_os2.h"
#include "svc_log.h"
#include "svc_monitoring.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lwip.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"

extern struct netif gnetif;

#define MONITOR_DECLARE_TASK_SYMBOLS(name, handleSym, attrSym, isCurrent) \
    extern osThreadId_t handleSym; \
    extern const osThreadAttr_t attrSym;
MONITORED_TASK_LIST(MONITOR_DECLARE_TASK_SYMBOLS)
#undef MONITOR_DECLARE_TASK_SYMBOLS

typedef struct
{
    const char* name;
    osThreadId_t* handle_ref;
    const osThreadAttr_t* attr_ref;
    uint8_t is_current_task;
} monitored_task_t;

#define MONITOR_TASK_ENTRY(displayName, handleSym, attrSym, isCurrent) \
    { \
        .name = displayName, \
        .handle_ref = &handleSym, \
        .attr_ref = &attrSym, \
        .is_current_task = isCurrent \
    },

static const monitored_task_t g_monitored_tasks[] =
{
    MONITORED_TASK_LIST(MONITOR_TASK_ENTRY)
};

#undef MONITOR_TASK_ENTRY

static uint32_t Monitor_StackBytesToWords(uint32_t stack_bytes)
{
    return stack_bytes / (uint32_t)sizeof(StackType_t);
}


static void Monitor_CheckHeap(void)
{
    uint32_t free_heap =
        SvcMonitoring_GetFreeHeapBytes();

    uint32_t min_heap =
        SvcMonitoring_GetMinEverFreeHeapBytes();

    LOGI("Heap free=%lu minEver=%lu bytes",
         free_heap,
         min_heap);

    if (free_heap < HEAP_CRITICAL_THRESHOLD_BYTES)
    {
        LOGE("Heap critical! free=%lu bytes", free_heap);
    }
    else if (free_heap < HEAP_WARN_THRESHOLD_BYTES)
    {
        LOGW("Heap warning! free=%lu bytes", free_heap);
    }

    if (min_heap < HEAP_CRITICAL_THRESHOLD_BYTES)
    {
        LOGE("Heap minEver critical! minEver=%lu bytes", min_heap);
    }
    else if (min_heap < HEAP_WARN_THRESHOLD_BYTES)
    {
        LOGW("Heap minEver warning! minEver=%lu bytes", min_heap);
    }
}

static void Monitor_CheckStack(
    const char* task_name,
    const svc_task_stack_info_t* stack)
{
    if ((task_name == NULL) || (stack == NULL))
    {
        return;
    }

    LOGI("%s stack total=%lu usedMax=%lu freeMin=%lu usage=%lu%%",
         task_name,
         stack->total_words,
         stack->max_used_words,
         stack->min_free_words,
         stack->usage_percent);

    if (stack->min_free_words < STACK_CRITICAL_THRESHOLD_WORDS)
    {
        LOGE("%s stack critical!", task_name);
    }
    else if (stack->min_free_words < STACK_WARN_THRESHOLD_WORDS)
    {
        LOGW("%s stack warning!", task_name);
    }
}

void Monitor_NetworkStats(void)
{

    static uint8_t prev_link_up = 0xFFu;
    static uint8_t prev_netif_up = 0xFFu;

    uint8_t link_up = netif_is_link_up(&gnetif) ? 1u : 0u;
    uint8_t netif_up = netif_is_up(&gnetif) ? 1u : 0u;

    if ((link_up != prev_link_up) || (netif_up != prev_netif_up))
    {
        prev_link_up = link_up;
        prev_netif_up = netif_up;

        LOGI("IP : %s", ip4addr_ntoa(netif_ip4_addr(&gnetif))); 
        LOGI("NETMASK : %s", ip4addr_ntoa(netif_ip4_netmask(&gnetif))); 
        LOGI("GW : %s", ip4addr_ntoa(netif_ip4_gw(&gnetif))); 
        LOGI("Link : %s", netif_is_link_up(&gnetif) ? "UP" : "DOWN"); 
        LOGI("NetIf : %s", netif_is_up(&gnetif) ? "UP" : "DOWN"); 
        LOGI("Flags = 0x%04X", gnetif.flags); 
        LOGI("HWADDR=%02X:%02X:%02X:%02X:%02X:%02X", 
            gnetif.hwaddr[0], 
            gnetif.hwaddr[1], 
            gnetif.hwaddr[2], 
            gnetif.hwaddr[3], 
            gnetif.hwaddr[4], 
            gnetif.hwaddr[5]);
    }

}

void MonitorTask(void *argument)
{
    (void)argument;

    LOGI("MonitorTask started");

    for (;;)
    {
    	char stats_buf[512];

        Monitor_NetworkStats();

    	vTaskGetRunTimeStats(stats_buf);
    	LOGI("\r\nTask Runtime Stats:\r\n%s", stats_buf);

        Monitor_CheckHeap();

        for (uint32_t i = 0;
             i < (sizeof(g_monitored_tasks) / sizeof(g_monitored_tasks[0]));
             i++)
        {
            if ((g_monitored_tasks[i].is_current_task == 0u) &&
                (*g_monitored_tasks[i].handle_ref == NULL))
            {
                LOGW("%s task handle is NULL", g_monitored_tasks[i].name);
                continue;
            }

            svc_task_stack_info_t stack = {0};

            void* handle =
                g_monitored_tasks[i].is_current_task ? NULL : (void*)(*g_monitored_tasks[i].handle_ref);

            uint32_t total_stack_words =
                Monitor_StackBytesToWords(
                    g_monitored_tasks[i].attr_ref->stack_size);

            if (SvcMonitoring_GetTaskStackInfo(
                    handle,
                    total_stack_words,
                    &stack))
            {
                Monitor_CheckStack(g_monitored_tasks[i].name, &stack);
            }
        }

        osDelay(MONITOR_PERIOD_MS);
    }

}
