#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char c, *p, buf[512], *arg[4];
    if (argc != 3) {
        fprintf(2, "Usage: xargs [command] [parameter]\n");
        exit(1);
    }
    p = buf;
    while (read(0, &c, sizeof(c)) == sizeof(c)) {
        if (c != '\n') {
            *p ++ = c;
        } else {
            *p = '\0';
            if (fork() == 0) {
                arg[0] = argv[1];
                arg[1] = argv[2];
                arg[2] = buf;
                arg[3] = argv[3];
                exec(arg[0], arg);
                exit(0);
            } else {
                wait(0);
            }
            p = buf;
        }
    }
    exit(0);
}