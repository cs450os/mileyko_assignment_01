/* CS 450 — Programming Assignment 1: Process Creation
 * STARTER FILE — this is the file you implement.
 *
 * main.c is complete: it parses the command line and calls the functions
 * below. You should not need to modify it or procs.h.
 *
 * SUGGESTED ORDER OF WORK
 *   1. emit(), emit_node(), emit_reap(), emit_info()  — nothing can be graded
 *      until the records come out in the right format.
 *   2. cmd_fork1()      — the smallest possible fork.
 *   3. cmd_fanout()     — n children of ONE parent. Read the warning below.
 *   4. cmd_status()     — wait() and the status macros.
 *   5. cmd_chain()      — recursion down a line.
 *   6. cmd_tree()       — recursion with branching.
 *   7. cmd_execdemo() + cmd_helper()  — fork then exec.
 *   8. cmd_orphan(), cmd_zombie(), proc_state()
 *
 * THREE RULES THAT WILL SAVE YOU HOURS
 *
 *   (a) USE write(2), NOT printf(3), for records.  stdio buffers: if stdout is
 *       a pipe or a file, text you "printed" may still be in the buffer when
 *       you fork, and the CHILD INHERITS A COPY OF THAT BUFFER and prints it
 *       again. The emit() helper below is where you solve this once.
 *
 *   (b) A CHILD MUST NEVER FALL OUT OF THE LOOP THAT CREATED IT.  End every
 *       child branch with _exit(). Forget it once in cmd_fanout() and n
 *       iterations create 2^n processes instead of n+1.
 *
 *   (c) USE _exit(), NOT exit(), IN A CHILD.  exit() runs atexit handlers and
 *       flushes stdio buffers the child inherited — which prints the parent's
 *       buffered output a second time.
 */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "procs.h"

/* ============================================================== TASK 1 ==== */
/* Format the message and write it to file descriptor 1 with a single write().
 * One write() per record keeps each line atomic, so concurrent children cannot
 * interleave halfway through a line.
 *
 * Hint: vsnprintf() into a char buf[512], then write(1, buf, n). */
void emit(const char *fmt, ...)
{
    (void)fmt;
    /* TODO */
}

/* NODE <label> pid=<pid> ppid=<ppid> */
void emit_node(const char *label)
{
    (void)label;
    /* TODO */
}

/* REAP <label> pid=<pid> status=exited:<code>
 * REAP <label> pid=<pid> status=signaled:<signo>
 * Use WIFEXITED/WEXITSTATUS and WIFSIGNALED/WTERMSIG. */
void emit_reap(const char *label, pid_t pid, int status)
{
    (void)label; (void)pid; (void)status;
    /* TODO */
}

/* INFO <key>=<value> */
void emit_info(const char *key, const char *valfmt, ...)
{
    (void)key; (void)valfmt;
    /* TODO */
}

/* ============================================================== TASK 2 ==== */
/* Read /proc/<pid>/stat and return the state character ('R','S','Z',...).
 * Return '?' if the file cannot be opened, which is what happens once the
 * process has been reaped and no longer exists.
 *
 * WATCH OUT: the second field is the executable name in parentheses and it can
 * itself contain spaces or a ')'. Find the LAST ')' in the line; the state is
 * two characters after it. */
char proc_state(pid_t pid)
{
    (void)pid;
    return '?';   /* TODO */
}

/* ============================================================== TASK 3 ==== */
/* One fork. Emit NODE for yourself, fork, have the child emit its own NODE and
 * _exit(0), and have the parent wait for it and emit REAP.
 *
 * Also emit:
 *   INFO parent_sees_fork_return_is_child_pid=<the value fork() returned>
 *   INFO child_sees_fork_return=0
 *   INFO child_getppid_equals_root=1   (from the child, after checking) */
int cmd_fork1(void)
{
    /* TODO */
    return 0;
}

/* ============================================================== TASK 4 ==== */
/* n children, ALL with the same parent. Labels c0..c(n-1).
 * Child i must _exit(i % 100) so the parent can check the code it gets back.
 * The parent waits for every child and emits one REAP each, then
 *   INFO children_created=<n>
 *
 * This is where rule (b) at the top of the file matters. */
int cmd_fanout(int n)
{
    (void)n;
    /* TODO */
    return 0;
}

/* ============================================================== TASK 5 ==== */
/* A chain n links deep: n0 -> n1 -> ... -> n<n>.
 * Every process forks exactly one child and waits for it.
 * The root emits INFO chain_depth=<n> at the end. */
int cmd_chain(int n)
{
    (void)n;
    /* TODO */
    return 0;
}

/* ============================================================== TASK 6 ==== */
/* A complete k-ary tree of depth d. Label the root "r" and each child
 * "<parent>.<index>", so a depth-2 binary tree is:
 *   r, r.0, r.1, r.0.0, r.0.1, r.1.0, r.1.1
 * Every parent waits for all of its children. The root also emits
 *   INFO expected_nodes=<(k^(d+1)-1)/(k-1), or d+1 when k==1> */
int cmd_tree(int k, int d)
{
    (void)k; (void)d;
    /* TODO */
    return 0;
}

/* ============================================================== TASK 7 ==== */
/* Three children that exit with codes 0, 1 and 42 (labels e0, e1, e2), and a
 * fourth (label "sig") that you kill with SIGTERM instead. Emit a REAP for
 * each. Finish with
 *   INFO exit_status_is_8_bits=<300 & 0xFF>
 * and be ready to explain that number in your report. */
int cmd_status(void)
{
    /* TODO */
    return 0;
}

/* ============================================================== TASK 8 ==== */
/* fork(), then in the child exec THIS SAME PROGRAM with the arguments
 * "helper" "execed".  `self` is argv[0].
 * Emit, from the right processes:
 *   INFO parent_recorded_child_pid=<pid fork returned>
 *   INFO child_pid_before_exec=<getpid() in the child, before exec>
 * and, in cmd_helper, NODE execed plus INFO pid_after_exec=<getpid()>.
 * If all three PIDs are equal you have shown what exec does. */
int cmd_execdemo(const char *self)
{
    (void)self;
    /* TODO */
    return 0;
}

int cmd_helper(const char *label)
{
    (void)label;
    /* TODO */
    return 0;
}

/* ============================================================== TASK 9 ==== */
/* Show re-parenting. Build root -> mid -> orphan. The orphan reports its ppid,
 * waits for mid to die, then reports its ppid again:
 *   NODE orphan pid=... ppid=...
 *   INFO orphan_ppid_before=<mid's pid>
 *   INFO orphan_ppid_after=1
 *
 * The orphan is not the root's child, so the root cannot wait() for it — use a
 * pipe(2) so the orphan's records still reach stdout in order. Make mid live
 * just long enough for the orphan to observe the original ppid. */
int cmd_orphan(void)
{
    /* TODO */
    return 0;
}

/* ============================================================= TASK 10 ==== */
/* Show a zombie. Fork a child that _exit(7)s immediately. WITHOUT waiting,
 * give it a moment to finish, then report proc_state(child) — it must be 'Z'.
 * Then wait for it, emit the REAP, and report proc_state() again ('?').
 *   INFO state_before_wait=Z
 *   INFO state_after_wait=? */
int cmd_zombie(void)
{
    /* TODO */
    return 0;
}
