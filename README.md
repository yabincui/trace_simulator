
This directory contains code to simulate the tracing macros used in kernel.
This is intend to understand that.

There are two types of tracing macros:
old one is DECLARE_TRACE, DEFINE_TRACE.
new one is TRACE_EVENT.

Step 1: Read the doc as much as you can.

tracepoints.txt

A tracepoint placed in code provides a hook to call a function that you can provide
at runtime. A tracepoint can be on/off. You can pass some parameters to the hook.

Two elements are required:
  A tracepoint definition, placed in a header file.
  The tracepoint statement, in C code.

In the header file, include/trace/events/subsys.h.

  #undef TRACE_SYSTEM
  #define TRACE_SYSTEM subsys
  
  #if !defined(_TRACE_SUBSYS_H) || defined(TRACE_HEADER_MULTI_READ)
  #define _TRACE_SUBSYS_H
  
  #include <linux/tracepoint.h>
  
  DECLARE_TRACE(subsys_eventname,
    TP_PROTO(int_firstarg, struct task_struct* p),  // prototype to call your hook.
    TP_ARGS(firstarg, p));  // parameter names.
  
  #endif
  
  #include <trace/define_trace.h>
  
In subsys/file.c:
  
  #include <trace/events/subsys.h>
  
  #define CREATE_TRACE_POINTS
  DEFINE_TRACE(subsys_eventname);
  
  void somefact() {
    trace_subsys_eventname(arg, task);
  }

All trace_<tracepoint>() has a matching trace_<tracepoint>_enabled() function.













  
  
  