#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("error\n");
        exit(0);
    }

    int t = atoi(argv[1]);
    printf("%d\n", t);
    sleep(t);
    exit(0);
}