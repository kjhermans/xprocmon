#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "xprocmon.h"

int xprocmon_stat
  (pid_t pid, xprocmon_t* pm)
{
  char path[ 256 ];
  char buf[ 1024 ];
  char* str = buf;

  char           state = 0;
  int            ppid = 0, pgrp = 0, session = 0, tty_nr = 0,
                 tpgid = 0, exit_signal = 0, processor = 0;
  unsigned       flags = 0, rt_priority = 0, policy = 0;
  unsigned long  minflt = 0, cminflt = 0, majflt = 0, cmajflt = 0,
                 utime = 0, stime = 0, vsize = 0, rsslim = 0,
                 startcode = 0, endcode = 0, startstack = 0, kstkesp = 0,
                 kstkeip = 0, signal = 0, blocked = 0, sigignore = 0,
                 sigcatch = 0, wchan = 0, nswap = 0, cnswap = 0;
  long int       cutime = 0, cstime = 0, priority = 0, nice = 0,
                 num_threads = 0, itrealvalue = 0, rss = 0;
  unsigned long long
                 starttime = 0;

  snprintf(path, sizeof(path), "/proc/%d/stat", pid);
  int fd = open(path, O_RDONLY, 0644);
  if (fd >= 0) {
    ssize_t r = read(fd, buf, sizeof(buf));
    if (r > -1) {
      close(fd);
      if (r == sizeof(buf)) { --r; }
      buf[ r ] = 0;
      str = buf;
      int _pid = strtol(str, &str, 10); (void)_pid;
      if (str[ 0 ] == 0) {
        return ~0;
      }
      ++str;
      str = strchr(str, ' ');
      if (str[ 0 ] == 0) {
        return ~0;
      }
      ++str;
      int s = sscanf(str,
        "%c %d %d %d %d %d %u "
        "%lu %lu %lu %lu "
        "%lu %lu %ld %ld "
        "%ld %ld "
        "%ld %ld %llu "
        "%lu %ld %lu "
        "%lu %lu %lu %lu %lu "
        "%lu %lu %lu %lu %lu "
        "%lu %lu %d "
        "%d %u %u "
        , &state
        , &ppid
        , &pgrp
        , &session
        , &tty_nr
        , &tpgid
        , &flags
        , &minflt , &cminflt , &majflt , &cmajflt
        , &utime, &stime, &cutime, &cstime
        , &priority, &nice
        , &num_threads, &itrealvalue, &starttime
        , &vsize, &rss, &rsslim
        , &startcode, &endcode, &startstack, &kstkesp, &kstkeip
        , &signal, &blocked, &sigignore, &sigcatch, &wchan
        , &nswap, &cnswap, &exit_signal
        , &processor, &rt_priority, &policy
      );
      (void)s;
    }
    pm->stime = stime;
    pm->cstime = cstime;
    pm->numthreads = num_threads;
  }
  return 0;
}
