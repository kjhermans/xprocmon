#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#include <sys/wait.h>

#include "xprocmon.h"

extern char** environ;
static pid_t pid = 0;

static
void sighandler
  (int signum)
{
  fprintf(stderr, "Signal trapped %d\n", signum);
  switch (signum) {
  case SIGINT:
  case SIGTERM:
  case SIGCHLD:
    { int status = 0; waitpid(pid, &status, 0); exit(status); }
  }
}

int main
  (int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "Argument to run must be provided.\n");
    exit(-1);
  }
  signal(SIGINT, sighandler);
  signal(SIGTERM, sighandler);
  signal(SIGCHLD, sighandler);
  switch (pid = fork()) {
  case -1:
    perror("fork");
    exit(-2);
  case 0:
    if (execve(argv[ 1 ], &(argv[ 1 ]), environ)) {
      exit(errno);
    }
    exit(0);
  default:
    break;
  }
  xprocmon_window(pid);
  return 0;
}
