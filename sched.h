#ifndef _SCHED_H
#define _SCHED_H

struct my_task_struct {
  char name[16];
};

int sched_function(struct my_task_struct* prev, struct my_task_struct* next);

#endif  // _SCHED_H
