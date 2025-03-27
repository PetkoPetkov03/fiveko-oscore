#define NOB_IMPLEMENTATION
#include "./noblib/nob.h"
#define BUILD "./build/"
#define LIBS "./libs/"
#define EXAMPLES "./examples/"

void nob_atempt_append(Nob_Cmd *cmd, char* command)
{
  nob_cmd_append(cmd, command);
}

void nob_mullti_append(Nob_Cmd* cmd, char** base, size_t size)
{
  for(int i = 0; i < size; i++) {
    nob_atempt_append(cmd, base[i]);
  }
}

int main(int argc, char** argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};

  if(!nob_mkdir_if_not_exists(BUILD)) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"queue")) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"atomic")) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"mutex")) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"semaphor")) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"threads")) return 1;
  if(!nob_mkdir_if_not_exists(BUILD"task")) return 1;

  char* base[4] = {
    "gcc",
    "-Wall",
    "-Wextra",
    "-O3"
};

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"queue/que.o", "-c", LIBS"queue/que.c");

  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"task/task.o", "-c",
  LIBS"task/task.c");

  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"atomic/aint.o", "-c", LIBS"atomic/aint.c");

  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"mutex/mutex.o", "-c", LIBS"mutex/mutex.c");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"semaphor/sem.o", "-c", LIBS"semaphor/sem.c");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;


  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", BUILD"threads/threads.o", "-c",
  LIBS"threads/threads.c");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", EXAMPLES"thread-exp/thread.a",
                 EXAMPLES"thread-exp/thread.c", BUILD"threads/threads.o");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", EXAMPLES"aint-exmp/aintex.a",
  EXAMPLES"aint-exmp/aintex.c", BUILD"atomic/aint.o");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;


  nob_mullti_append(&cmd, base, 4);
  nob_cmd_append(&cmd, "-o", EXAMPLES"tcb/tcb.a",
  EXAMPLES"tcb/tcb.c", BUILD"task/task.o", BUILD"queue/que.o");
  if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;
  // nob_mullti_append(&cmd, base, 4);
  // nob_cmd_append(&cmd, "-o", EXAMPLES"queue-ex/q.a",
  // EXAMPLES"queue-ex/q.c", BUILD"queue/que.o");
  // if(!nob_cmd_run_sync_and_reset(&cmd)) return 1;

  return 0;
}
