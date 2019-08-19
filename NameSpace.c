#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

static int child_fn() {
  printf("PID: %ld\n", (long)getpid());
  printf("PPID: %ld\n", (long)getppid());
  return 0;
}

int main() {
  printf("Without CLONE_NEWPID----\n");
  pid_t child_pid = clone(child_fn, child_stack+1048576,  SIGCHLD, NULL);//CLONE_NEWPID
  printf("clone() = %ld\n", (long)child_pid);

  waitpid(child_pid, NULL, 0);

  printf("with CLONE_NEWPID----\n");
  pid_t child_pid_1 = clone(child_fn, child_stack+1048576, CLONE_NEWPID | SIGCHLD, NULL);//
  printf("clone() = %ld\n", (long)child_pid_1);

  waitpid(child_pid_1, NULL, 0);
  return 0;
}


