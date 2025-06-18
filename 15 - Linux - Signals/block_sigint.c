#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t new_mask, old_mask;

    // Initialize a signal set and add SIGINT to it
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

    // Block SIGINT
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT blocking program started. PID: %d\n", getpid());
    printf("SIGINT is now blocked. Try pressing Ctrl+C.\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

