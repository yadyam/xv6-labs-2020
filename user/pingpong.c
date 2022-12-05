#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    char buf[8];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        int cpid = getpid();
        read(p1[0], buf, 1);
        fprintf(1, "%d: received ping\n", cpid);
        write(p2[1], "a", 2);
    } else {
        int ppid = getpid();
        write(p1[1], "a", 2);
        read(p2[0], buf, 1);
        fprintf(1, "%d: received pong\n", ppid);
    }
    exit(0);
}