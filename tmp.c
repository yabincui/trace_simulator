#define TRACING_SYSTEM sched



#define xstr(s) str(s)
#define str(s) #s
#define foo 4
xstr(foo)


#define _INCLUDE_FILE(file) <trace_## file.h>

#define INCLUDE_FILE(file) _INCLUDE_FILE(file)

INCLUDE_FILE(TRACING_SYSTEM)

#define _INCLUDE_FILE2(file)  "trace_" #file ".h"

#define INCLUDE_FILE2(file) _INCLUDE_FILE2(file)

INCLUDE_FILE2(TRACING_SYSTEM)


#define __stringify_1(x...)  #x
#define __stringify(x...)  __stringify_1(x)

#define _INCLUDE_FILE3(file) __stringify(trace_ ## file.h)

#define INCLUDE_FILE3(file) _INCLUDE_FILE3(file)

INCLUDE_FILE3(TRACING_SYSTEM)

#define __CONCAT_TWO_1(a, b) a ## b
#define __CONCAT_TWO(a, b) __CONCAT_TWO_1(a, b)


__stringify(__CONCAT_TWO(trace_, TRACING_SYSTEM.h))
