/**
 * Initialization code heavily modified but inspired from an ECE568 lab.
 * Ensures that the stack of the thread running the demo_main is starting from a fixed and known address.
 * This is for the sake of practice, helps stop the effects of stack size and address variation.
 * The code that would normally be in main(), is in a function called demo_main() instead.
 * See: https://www.exploit-db.com/papers/13162
 */

#define STACK_LOCATION 0x46930000
#define STACK_SIZE     (128 * 1024)

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

extern int demo_main (int argc, char *argv[]);

typedef struct main_thread_args {
    int argc;
    char **argv;
    int *rc;
} main_thread_args_t;

void* demo_main_thread(void *arg) {
    main_thread_args_t *main_args = (main_thread_args_t *)arg;
    *main_args->rc = demo_main(main_args->argc, main_args->argv);
    return main_args->rc;
}

int main(int argc, char *argv[]) {
    size_t demo_stack_size = STACK_SIZE;
    void *demo_stack = (void *)STACK_LOCATION;

    // Ensure the demo stack size is an integer multiple of the system page size.
    const int page_size = getpagesize();
    demo_stack_size += page_size - (demo_stack_size % page_size);

    // Allocate a new stack at a fixed location: demo_stack.
    const void *mmap_result = mmap(demo_stack, (demo_stack_size + page_size),
                                   PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_FIXED | MAP_PRIVATE, -1,(off_t) 0);
    assert(mmap_result != MAP_FAILED);

    int *rc = malloc(sizeof(int));
    main_thread_args_t args = {argc, argv, rc};

    // Create a new pthread to run demo_main() with the artificially fixed stack.
    pthread_t demo_thread;
    pthread_attr_t pthread_attr;
    assert(pthread_attr_init(&pthread_attr) == 0);
    assert(pthread_attr_setstack(&pthread_attr, demo_stack, demo_stack_size) == 0);
    assert(pthread_create(&demo_thread, &pthread_attr, demo_main_thread, (void *)&args) == 0);

    // Wait for the thread running demo_main() to exit, and capture its return value.
    int *demo_thread_return = NULL;
    assert(pthread_join(demo_thread, (void **) &demo_thread_return) == 0);
    return (*demo_thread_return);
}