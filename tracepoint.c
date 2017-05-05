#include "tracepoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "logging.h"

static int tracepoint_add_func(struct tracepoint* tp, struct tracepoint_func* func) {
  if (tp->regfunc && !tp->key) {
    tp->regfunc();
  }
  struct tracepoint_func* tp_funcs = tp->funcs;
  bool exist = false;
  int nr_probes = 0;
  if (tp_funcs) {
    for (nr_probes = 0; tp_funcs[nr_probes].func; nr_probes++) {
      if (tp_funcs[nr_probes].func == func->func &&
          tp_funcs[nr_probes].data == func->data) {
        exist = true;
        break;
      }
    }
  }
  if (!exist) {
    struct tracepoint_func* new_funcs = (struct tracepoint_func*)calloc(
        nr_probes + 2, sizeof(struct tracepoint_func));
    CHECK(new_funcs);
    if (tp_funcs) {
      memcpy(new_funcs, tp_funcs, nr_probes * sizeof(struct tracepoint_func));
    }
    new_funcs[nr_probes] = *func;
    new_funcs[nr_probes+1].func = NULL;
    tp->funcs = new_funcs;
    if (tp_funcs) {
      free(tp_funcs);
    }
  }
  if (!tp->key) {
    tp->key++;
  }
}

static int tracepoint_remove_func(struct tracepoint* tp, struct tracepoint_func* func) {
  struct tracepoint_func* tp_funcs = tp->funcs;
  int nr_probes = 0;
  int nr_delete = 0;
  if (tp_funcs->func) {
    for (nr_probes = 0; tp_funcs[nr_probes].func; nr_probes++) {
      if (tp_funcs[nr_probes].func == func->func &&
          tp_funcs[nr_probes].data == func->data) {
        nr_delete++;
      }
    }
  }
  if (nr_probes - nr_delete == 0) {
    tp->funcs = NULL;
  } else {
    struct tracepoint_func* new_funcs = (struct tracepoint_func*)calloc(
        nr_probes - nr_delete + 1, sizeof(struct tracepoint_func));
    CHECK(new_funcs);
    int i = 0;
    int j = 0;
    for (i = 0; i < nr_probes; i++) {
      if (tp_funcs[i].func != func->func || tp_funcs[i].data != func->data) {
        new_funcs[j++] = tp_funcs[i];
      }
    }
    tp->funcs = new_funcs;
  }
  free(tp_funcs);

  if (!tp->funcs) {
    if (tp->unregfunc && tp->key) {
      tp->unregfunc();
    }
    if (tp->key) {
      tp->key--;
    }
  }
  return 0;
}

int tracepoint_probe_register(struct tracepoint* tp, void* probe, void* data) {
  struct tracepoint_func tp_func;
  tp_func.func = probe;
  tp_func.data = data;
  return tracepoint_add_func(tp, &tp_func);
}

int tracepoint_probe_unregister(struct tracepoint* tp, void* probe, void* data) {
  struct tracepoint_func tp_func;
  tp_func.func = probe;
  tp_func.data = data;
  return tracepoint_remove_func(tp, &tp_func);
}
