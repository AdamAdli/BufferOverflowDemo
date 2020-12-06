#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *arg, char *out) {
    strcpy(out, arg); // This is an unsafe `strcpy`.
    return (0); // Can we over-write foo's return address in the stack?
}

int demo_main(int argc, char *argv[]) {
    int t = 2;
    char buf[124];

    printf("Demo 1 running.\n");
    if (argc != t) {
        fprintf(stderr, "demo_target: argc != 2\n");
        exit(EXIT_FAILURE);
    }

    foo(argv[1], buf);
    return (0);
}
