#include "xprocmon.h"

/**
 *
 */
void xprocmon_data_examine
  (xprocmon_data_t* pmd)
{
  xprocmon_t* pm = &(pmd->points[ pmd->offset ]);

  if (pm->mem.stack > pmd->graph_height) {
    pmd->graph_height = pm->mem.stack;
  }
  if (pm->mem.heap > pmd->graph_height) {
    pmd->graph_height = pm->mem.heap;
  }
/*
  if (pm->mem.total > pmd->graph_height) {
    pmd->graph_height = pm->mem.total;
  }
*/
}
