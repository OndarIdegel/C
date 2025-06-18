#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t mask;
    int signo;

    // Initialize a signal set and add SIGUSR1 to it
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    // Block SIGUSR1
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("Event-loop with sigwait() started. PID: %d\n", getpid());
    fflush(stdout);
    printf("SIGUSR1 is blocked. Waiting for SIGUSR1...\n");
    fflush(stdout);

    while (1) {
        // Wait for a signal specified in \'mask\'
        if (sigwait(&mask, &signo) == -1) {
            perror("sigwait");
            exit(EXIT_FAILURE);
        }

        if (signo == SIGUSR1) {
            printf("Received SIGUSR1 signal in event loop!\n");
            fflush(stdout);
        }
    }

    return 0;
}
