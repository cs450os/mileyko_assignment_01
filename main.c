/* CS 450 — PA1 reference driver.
 *
 *   ./procs SUBCOMMAND [ARGS]
 *
 *   fork1              one child; show fork()'s two return values
 *   fanout N           N children of a single parent
 *   chain N            a chain N links deep
 *   tree K D           a complete K-ary tree of depth D
 *   status             exit codes, and a child killed by a signal
 *   execdemo           fork + exec; the PID survives the exec
 *   orphan             a child outlives its parent and is re-parented
 *   zombie             an unreaped child sits in state Z
 *   helper LABEL       internal: the program execdemo runs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "procs.h"

static int usage(const char *me)
{
    fprintf(stderr,
        "usage: %s SUBCOMMAND [ARGS]\n"
        "  fork1 | fanout N | chain N | tree K D | status | execdemo |\n"
        "  orphan | zombie\n", me);
    return 1;
}

static int posint(const char *s, int lo, int hi, int *out)
{
    if (!s || !*s) return 0;
    char *end;
    long v = strtol(s, &end, 10);
    if (*end || v < lo || v > hi) return 0;
    *out = (int)v;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 2) return usage(argv[0]);
    const char *cmd = argv[1];

    if (!strcmp(cmd, "fork1"))    return cmd_fork1();
    if (!strcmp(cmd, "status"))   return cmd_status();
    if (!strcmp(cmd, "execdemo")) return cmd_execdemo(argv[0]);
    if (!strcmp(cmd, "orphan"))   return cmd_orphan();
    if (!strcmp(cmd, "zombie"))   return cmd_zombie();

    if (!strcmp(cmd, "helper")) {
        if (argc < 3) return usage(argv[0]);
        return cmd_helper(argv[2]);
    }
    if (!strcmp(cmd, "fanout")) {
        int n;
        if (argc < 3 || !posint(argv[2], 0, 200, &n)) {
            fprintf(stderr, "fanout: N must be an integer 0..200\n");
            return 1;
        }
        return cmd_fanout(n);
    }
    if (!strcmp(cmd, "chain")) {
        int n;
        if (argc < 3 || !posint(argv[2], 0, 200, &n)) {
            fprintf(stderr, "chain: N must be an integer 0..200\n");
            return 1;
        }
        return cmd_chain(n);
    }
    if (!strcmp(cmd, "tree")) {
        int k, d;
        if (argc < 4 || !posint(argv[2], 1, 8, &k) ||
            !posint(argv[3], 0, 6, &d)) {
            fprintf(stderr, "tree: K must be 1..8 and D must be 0..6\n");
            return 1;
        }
        return cmd_tree(k, d);
    }
    return usage(argv[0]);
}
