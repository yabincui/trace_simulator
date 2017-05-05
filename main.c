#include <stdio.h>
#include <string.h>

#include "sched.h"


int main() {
  struct my_task_struct prev;
  struct my_task_struct next;

  strcpy(prev.name, "prev");
  strcpy(next.name, "next");

  sched_function(&prev, &next);
  return 0;
}
