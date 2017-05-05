#ifndef _TRACEPOINT_H
#define _TRACEPOINT_H

#include <stdbool.h>

struct tracepoint_func {
  void* func;
  void* data;
};

struct tracepoint {
  const char* name;
  int key;
  void (*regfunc)(void);
  void (*unregfunc)(void);
  struct tracepoint_func* funcs;
};

int tracepoint_probe_register(struct tracepoint* tp, void* probe, void* data);

int tracepoint_probe_unregister(struct tracepoint* tp, void* probe, void* data);

#endif // _TRACEPOINT_H

#ifndef DECLARE_TRACE

#define TP_PROTO(args...) args
#define TP_ARGS(args...) args

#define PARAMS(args...) args

#define __DO_TRACE(tp, proto, args) \
  do {  \
    struct tracepoint_func *it_func_ptr;  \
    void* it_func;  \
    void* __data;  \
    it_func_ptr = (tp)->funcs; \
    if (it_func_ptr) {  \
      do {  \
        it_func = it_func_ptr->func;  \
        __data = (it_func_ptr)->data;  \
        ((void(*)(proto))(it_func))(args); \
      } while ((++it_func_ptr)->func); \
    }  \
  } while (0)



#define __DECLARE_TRACE(name, proto, args, data_proto, data_args) \
  extern struct tracepoint __tracepoint_##name; \
  static inline void trace_##name(proto) {  \
    if (__tracepoint_##name.key)  \
      __DO_TRACE(&__tracepoint_##name,  \
                 TP_PROTO(data_proto),  \
                 TP_ARGS(data_args));  \
  }  \
  static inline int register_trace_##name(void (*probe)(data_proto), void* data) { \
    return tracepoint_probe_register(&__tracepoint_##name, (void*)probe, data); \
  } \
  static inline int unregister_trace_##name(void (*probe)(data_probe), void* data) { \
    return tracepoint_probe_unregister(&__tracepoint_##name, (void*)probe, data); \
  } \
  static inline bool trace_##name##_enabled(void) { \
    return __tracepoint_##name.key ? true : false; \
  }


#define DECLARE_TRACE(name, proto, args) \
  __DECLARE_TRACE(name, PARAMS(proto), PARAMS(args), \
                  PARAMS(void* __data, proto), \
                  PARAMS(__data, args)) \


#define DEFINE_TRACE_FN(name, reg, unreg) \
  static const char __tpstrtab_##name[] = #name; \
  struct tracepoint __tracepoint_##name = \
  { __tpstrtab_##name, 0, reg, unreg, NULL }; \
  static struct tracepoint* const __tracepoint_ptr_##name = \
    &__tracepoint_##name;

#define DEFINE_TRACE(name) \
  DEFINE_TRACE_FN(name, NULL, NULL)

#endif // DECLARE_TRACE

#ifndef TRACE_EVENT

#define TRACE_EVENT(name, proto, args) \
  DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))

#endif  // TRACE_EVENT
