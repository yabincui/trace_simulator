
#include <stdio.h>

#include "sched.h"

#define CREATE_TRACE_POINTS
#include "trace_sched.h"

int sched_function(struct my_task_struct* prev, struct my_task_struct* next) {
  trace_sched_switch(prev, next);
  printf("sched from task %s to task %s\n", prev->name, next->name);
  return 0;
}
