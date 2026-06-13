#pragma once

/*
 * Central list of tasks observed by MonitorTask.
 * Add/remove items here without touching task_monitoring.c.
 *
 * Args: X(displayName, taskHandleSymbol, taskAttrSymbol, isCurrentTask)
 */
#define MONITORED_TASK_LIST(X) \
	X("App Manager", AppControlTaskHandle, AppControlTask_attributes, 0u) \
	X("Task Monitoring", MonitorTaskHandle, MonitorTask_attributes, 1u)

#define STACK_WARN_THRESHOLD_WORDS     (128u)
#define STACK_CRITICAL_THRESHOLD_WORDS (64u)

#define HEAP_WARN_THRESHOLD_BYTES      (4096u)
#define HEAP_CRITICAL_THRESHOLD_BYTES  (2048u)

#define MONITOR_PERIOD_MS              (5000u)
