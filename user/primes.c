#include "kernel/types.h"
#include "user/user.h"

void func(int rd) {
    int pri, tmp;
    if (read(rd, &pri, 4) != 4) return;
    fprintf(1, "prime %d\n", pri);
    int p[2];
    pipe(p);
    if (fork() == 0) {
        close(p[1]);
        func(p[0]);
        exit(0);
    } else {
        close(p[0]);
        while (read(rd, &tmp, 4) == 4) {
            if (tmp % pri == 0) continue;
            write(p[1], &tmp, 4);
        }
        close(p[1]);
        wait(0);
        exit(0);
    }
}

int
main(int argc, char *argv[]) 
{
    int p[2];
    pipe(p);
    if (fork() == 0) {
        close(p[1]);
        func(p[0]);
        exit(0);
    } else {
        close(p[0]);
        for (int i = 2; i <= 35; i ++) write(p[1], &i, 4);
        close(p[1]);
        wait(0);
        exit(0);
    }
    exit(0);
}