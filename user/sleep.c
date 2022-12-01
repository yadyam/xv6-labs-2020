#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
mian(int argc, char *argv[])
{
    int ticks;
    if (argc <= 1) {
        fprintf(2, "Usage: sleep [time]\n");
        exit(1);
    }

    ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}