#undef TRACE_SYSTEM
#define TRACE_SYSTEM sched

#if !defined(_TRACE_SCHED_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SCHED_H

#include "sched.h"
#include "tracepoint.h"

TRACE_EVENT(
    sched_switch,
    TP_PROTO(struct my_task_struct* prev, struct my_task_struct* next),
    TP_ARGS(prev, next)
);

#endif  // _TRACE_SCHED_H

#include "define_trace.h"
