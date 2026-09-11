/* CS 450 — Programming Assignment 1: Process Creation
 *
 * One executable, eight subcommands. Every subcommand prints a stream of
 * RECORDS describing the process tree it built, so you may check check the
 * *shape* of your tree without depending on PID values (which change on every
 * run) or on the order in which siblings happen to be scheduled.
 *
 * THE RECORD FORMAT — one per line, exactly:
 *
 *   NODE <label> pid=<pid> ppid=<ppid>
 *       printed by a process about ITSELF, once, as soon as it knows its role.
 *
 *   REAP <label> pid=<pid> status=exited:<code>
 *   REAP <label> pid=<pid> status=signaled:<signo>
 *       printed by a PARENT after wait()/waitpid() returns for that child.
 *
 *   INFO <key>=<value>
 *       a single fact the subcommand was asked to report.
 *
 * Labels are assigned by the program's own logic and are identical on every
 * run; PIDs are not. 
 */
#ifndef PROCS_H
#define PROCS_H

#include <sys/types.h>

#define LABEL_LEN 64

/* ---------------------------------------------------------------- output */
/* Print one record with write(2), not printf(3).
 *
 * WHY THIS MATTERS: stdio buffers. If stdout is a pipe or a file it is fully
 * buffered, so text you "printed" may still be sitting in the buffer when you
 * call fork() — and the child inherits a COPY of that buffer and prints it
 * again. write() goes straight to the file descriptor with no buffer to
 * duplicate. Analysis Question 1 asks you to demonstrate this.       */
void emit(const char *fmt, ...);

/* Convenience wrappers that produce exactly the records above. */
void emit_node(const char *label);                    /* uses getpid/getppid */
void emit_reap(const char *label, pid_t pid, int status);
void emit_info(const char *key, const char *valfmt, ...);

/* ------------------------------------------------------------ subcommands */
/* Each returns 0 on success. Each is called only in the ROOT process. */

int cmd_fork1   (void);              /* one child; show fork's two returns   */
int cmd_fanout  (int n);             /* n children, ONE parent               */
int cmd_chain   (int n);             /* a chain of depth n                   */
int cmd_tree    (int k, int d);      /* complete k-ary tree of depth d       */
int cmd_status  (void);              /* exit codes and a signalled child     */
int cmd_execdemo(const char *self);  /* fork + exec; the PID survives        */
int cmd_orphan  (void);              /* a child outlives its parent          */
int cmd_zombie  (void);              /* an unreaped child is state Z         */
int cmd_helper  (const char *label); /* the program exec'd by execdemo       */

/* Read the single-character state field from /proc/<pid>/stat.
 * Returns 'R','S','Z',... or '?' if the process is gone. */
char proc_state(pid_t pid);

#endif /* PROCS_H */
