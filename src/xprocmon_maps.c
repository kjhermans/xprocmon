#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "xprocmon.h"

struct maps {
  void* from;
  void* until;
  char* file;
};

static
int xprocmon_maps_line
  (char* line, struct maps* m)
{
  char* fromstr = line;
  char* untilstr;
  char* untilend;

  if (strlen(line) >= 73) {
    m->file = &(line[ 73 ]);
  }
  if ((untilstr = strchr(fromstr, '-')) == NULL) {
    return ~0;
  }
  *untilstr = 0;
  untilstr++;
  if ((untilend = strchr(untilstr, ' ')) == NULL) {
    return ~0;
  }
  *untilend = 0;
  m->from = (void*)strtoull(fromstr, 0, 16);
  m->until = (void*)strtoull(untilstr, 0, 16);
  return 0;
}

int xprocmon_maps
  (pid_t pid, xprocmon_t* pm)
{
  char path[ 256 ];
  char* maps, * line;
  struct maps map = { 0 };

  snprintf(path, sizeof(path), "/proc/%d/maps", pid);
  maps = dup_file_string(path);
  if (maps) {
    line = maps;
    while (1) {
      char* eol = strchr(line, '\n');
      if (eol) {
        *eol = 0;
      }
      if (xprocmon_maps_line(line, &map) == 0) {
        if (map.file) {
          if (0 == strcmp(map.file, "[heap]")) {
            pm->mem.heap = (map.until - map.from);
          } else if (0 == strcmp(map.file, "[stack]")) {
            pm->mem.stack = (map.until - map.from);
          }
        }
      }
      if (eol) { line = eol + 1; } else { break; }
    }
    free(maps);
  }
  return 0;
}
